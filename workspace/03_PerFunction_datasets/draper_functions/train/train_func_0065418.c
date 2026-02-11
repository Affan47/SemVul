ivinlib (qglobal, z, c, pz)
     struct sglobal *qglobal;
     const char *z;
     size_t c;
     char **pz;
{
  char *zalc;

  zalc = uuconf_malloc (qglobal->pblock, sizeof OLDCONFIGLIB - 1 + c);
  if (zalc == NULL)
    {
      qglobal->ierrno = errno;
      return UUCONF_MALLOC_FAILED | UUCONF_ERROR_ERRNO;
    }

  memcpy ((pointer) zalc, (pointer) OLDCONFIGLIB,
	  sizeof OLDCONFIGLIB - 1);
  memcpy ((pointer) (zalc + sizeof OLDCONFIGLIB - 1), (pointer) z, c);

  *pz = zalc;

  return UUCONF_SUCCESS;
}
