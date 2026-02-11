check_user ()
{
  gid_t *list;
  int i,n,found=0;
  uid_t uid, euid;

  if ((n = getgroups(0, NULL)) < 0) {
    found=0;
  }

  list = (gid_t*)malloc(sizeof (gid_t) * (n + 1));
  if (!list) {
#ifdef DEBUG
    debug("check_user() out of memory!\n");
#endif
    found=0;
  }

  n = getgroups(n, list);

  uid = getuid();
  euid = geteuid();

  if (uid == 0 && euid == 0) {
      found=1;
  }
  else {
     for (i = 0; i < n; i++)  {
#ifdef DEBUG
          debug("check_user() %lu (%s) %d %d\n", (unsigned long)list[i], get_group(list[i]), uid, euid);
#endif
          if ( (strcmp( get_group(list[i]), GROUP) == 0) && (euid == 0) ) {

            found=1;
         }
    }
  }
  free(list);
  return(found);
}
