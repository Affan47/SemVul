do_umount_all (void)
{
  FILE *fp;
  struct mntent *m;
  DECLARE_STRINGSBUF (mounts);
  size_t i;
  int r;


  aug_finalize ();
  hivex_finalize ();
  journal_finalize ();


  fp = setmntent ("/proc/mounts", "r");
  if (fp == NULL) {
    fprintf (stderr, "setmntent: %s: %m\n", "/proc/mounts");
    exit (EXIT_FAILURE);
  }

  while ((m = getmntent (fp)) != NULL) {

    if (sysroot_len > 0 && STREQ (m->mnt_dir, sysroot)) {
      if (add_string (&mounts, m->mnt_dir) == -1) {
        endmntent (fp);
        return -1;
      }
    }

    if (STRPREFIX (m->mnt_dir, sysroot) && m->mnt_dir[sysroot_len] == '/') {
      if (add_string (&mounts, m->mnt_dir) == -1) {
        endmntent (fp);
        return -1;
      }
    }
  }

  endmntent (fp);

  if (mounts.size > 0)
    qsort (mounts.argv, mounts.size, sizeof (char *), compare_longest_first);


  for (i = 0; i < mounts.size; ++i) {
    CLEANUP_FREE char *err = NULL;

    r = command (NULL, &err, str_umount, mounts.argv[i], NULL);
    if (r == -1) {
      reply_with_error ("umount: %s: %s", mounts.argv[i], err);
      free_stringslen (mounts.argv, mounts.size);
      return -1;
    }
  }

  free_stringslen (mounts.argv, mounts.size);

  return 0;
}
