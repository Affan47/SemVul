__gnat_portable_no_block_spawn (char *args[])
{

#if defined (__vxworks) || defined (__nucleus__) || defined (RTX)
  return -1;

#elif defined (_WIN32)

  HANDLE h = NULL;
  int pid;

  win32_no_block_spawn (args[0], args, &h, &pid);
  if (h != NULL)
    {
      add_handle (h, pid);
      return pid;
    }
  else
    return -1;

#else

  int pid = fork ();

  if (pid == 0)
    {

      if (execv (args[0], MAYBE_TO_PTR32 (args)) != 0)
#if defined (VMS)
	return -1;
#else
	_exit (1);
#endif
    }

  return pid;

  #endif
}
