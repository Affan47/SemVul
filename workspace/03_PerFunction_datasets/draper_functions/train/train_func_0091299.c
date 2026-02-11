do_vgcreate (const char *volgroup, char *const *physvols)
{
  int r, argc, i;
  CLEANUP_FREE char *err = NULL;
  CLEANUP_FREE const char **argv = NULL;

  argc = count_strings (physvols) + 3;
  argv = malloc (sizeof (char *) * (argc + 1));
  if (argv == NULL) {
    reply_with_perror ("malloc");
    return -1;
  }
  argv[0] = str_lvm;
  argv[1] = "vgcreate";
  argv[2] = volgroup;
  for (i = 3; i <= argc; ++i)
    argv[i] = physvols[i-3];

  r = commandv (NULL, &err, (const char * const*) argv);
  if (r == -1) {
    reply_with_error ("%s", err);
    return -1;
  }

  udev_settle ();

  return 0;
}
