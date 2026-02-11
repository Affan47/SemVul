my_init(void)
{
  char *str;

  if (my_init_done)
    return 0;

  my_init_done= 1;

  mysys_usage_id++;
  my_umask= 0660;
  my_umask_dir= 0700;


  if ((str= getenv("UMASK")) != 0)
    my_umask= (int) (atoi_octal(str) | 0600);

  if ((str= getenv("UMASK_DIR")) != 0)
    my_umask_dir= (int) (atoi_octal(str) | 0700);

  init_glob_errs();

  instrumented_stdin.m_file= stdin;
  instrumented_stdin.m_psi= NULL;
  mysql_stdin= & instrumented_stdin;

  if (my_thread_global_init())
    return 1;

#if defined(SAFE_MUTEX)
  safe_mutex_global_init();
#endif

#if defined(MY_PTHREAD_FASTMUTEX) && !defined(SAFE_MUTEX)
  fastmutex_global_init();
#endif


  if ((home_dir= getenv("HOME")) != 0)
    home_dir= intern_filename(home_dir_buff, home_dir);

  {
    DBUG_ENTER("my_init");
    DBUG_PROCESS((char*) (my_progname ? my_progname : "unknown"));
    my_win_init();
    DBUG_PRINT("exit", ("home: '%s'", home_dir));
#ifdef __WIN__
    win32_init_tcp_ip();
#endif
    DBUG_RETURN(0);
  }
}
