mount_proc (void)
{
  if (access ("/proc/uptime", R_OK) == -1) {
    mkdir ("/proc", 0755);

    if (verbose)
      fprintf (stderr, "supermin: mounting /proc\n");

    if (mount ("proc", "/proc", "proc", 0, "") == -1) {
      perror ("mount: /proc");

    }
  }
}
