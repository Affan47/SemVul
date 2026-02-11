checksum_start (const char *hostcpu, const char *appliance,
                const char *modpath, const char *initrd)
{
  pp = popen (shacmd, "w");
  if (pp == NULL)
    error (EXIT_FAILURE, errno, "popen: command failed: %s", shacmd);

  fprintf (pp, "%s %s %s %d\n",
           PACKAGE_STRING, hostcpu, modpath, geteuid ());
}
