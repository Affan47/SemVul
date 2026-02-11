srunner_fork_status (SRunner *sr)
{
  if (sr->fstat == CK_FORK_UNSPECIFIED) {
    char *env = getenv ("CK_FORK");
    if (env == NULL)
      return CK_FORK;
    if (strcmp (env,"no") == 0)
      return CK_NOFORK;
    else
      return CK_FORK;
  } else
    return sr->fstat;
}
