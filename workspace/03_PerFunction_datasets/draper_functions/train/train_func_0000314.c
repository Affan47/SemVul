daemonize (const ACE_TCHAR pathname[],
                bool close_all_handles,
                const ACE_TCHAR program_name[])
{
  ACE_TRACE ("ACE::daemonize");
#if !defined (ACE_LACKS_FORK)
  pid_t pid = ACE_OS::fork ();

  if (pid == -1)
    return -1;
  else if (pid != 0)
    ACE_OS::exit (0);


  ACE_OS::setsid ();

  ACE_OS::signal (SIGHUP, SIG_IGN);

  pid = ACE_OS::fork (program_name);

  if (pid != 0)
    ACE_OS::exit (0);


  if (pathname != 0)

    ACE_OS::chdir (pathname);

  ACE_OS::umask (0);


  if (close_all_handles)
    {
      for (int i = ACE::max_handles () - 1; i >= 0; i--)
        ACE_OS::close (i);

      int fd = ACE_OS::open ("/dev/null", O_RDWR, 0);
      if (fd != -1)
        {
          ACE_OS::dup2 (fd, ACE_STDIN);
          ACE_OS::dup2 (fd, ACE_STDOUT);
          ACE_OS::dup2 (fd, ACE_STDERR);

          if (fd > ACE_STDERR)
            ACE_OS::close (fd);
        }
    }

  return 0;
#else
  ACE_UNUSED_ARG (pathname);
  ACE_UNUSED_ARG (close_all_handles);
  ACE_UNUSED_ARG (program_name);

  ACE_NOTSUP_RETURN (-1);
#endif
}
