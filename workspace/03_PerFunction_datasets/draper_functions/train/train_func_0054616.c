cleanup_pidfile(void)
{
   if (getpid() == check_for_jpilot())
      unlink(pidfile);
}
