ipport (pglobal, argc, argv, pvar, pinfo)
     pointer pglobal;
     int argc ATTRIBUTE_UNUSED;
     char **argv;
     pointer pvar;
     pointer pinfo ATTRIBUTE_UNUSED;
{
  struct sglobal *qglobal = (struct sglobal *) pglobal;
  char **pz = (char **) pvar;
  size_t csize;

  csize = strlen (argv[1]) + 1;
  *pz = malloc (csize);
  if (*pz == NULL)
    {
      qglobal->ierrno = errno;
      return (UUCONF_MALLOC_FAILED
	      | UUCONF_ERROR_ERRNO
	      | UUCONF_CMDTABRET_EXIT);
    }
  memcpy ((pointer) *pz, (pointer) argv[1], csize);
  return UUCONF_CMDTABRET_EXIT;
}
