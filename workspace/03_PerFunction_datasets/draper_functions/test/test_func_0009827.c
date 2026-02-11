initgroups (const char *user, gid_t group)
{
#if defined NGROUPS_MAX && NGROUPS_MAX == 0


  return 0;

#else

  long int size;
  gid_t *groups;
  int ngroups;
  int result;


  long int limit = __sysconf (_SC_NGROUPS_MAX);

  if (limit > 0)

    size = MIN (limit, 64);
  else

    size = 16;

  groups = (gid_t *) malloc (size * sizeof (gid_t));
  if (__builtin_expect (groups == NULL, 0))

    return -1;

  ngroups = internal_getgrouplist (user, group, &size, &groups, limit);


  do
    result = setgroups (ngroups, groups);
  while (result == -1 && errno == EINVAL && --ngroups > 0);

  free (groups);

  return result;
#endif
}
