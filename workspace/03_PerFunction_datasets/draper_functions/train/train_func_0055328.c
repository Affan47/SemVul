main(int argc, char *argv[])
{
  CURLcode result = CURLE_OK;
  struct GlobalConfig global;
  memset(&global, 0, sizeof(global));

  main_checkfds();

#if defined(HAVE_SIGNAL) && defined(SIGPIPE)
  (void)signal(SIGPIPE, SIG_IGN);
#endif


  memory_tracking_init();


  result = main_init(&global);
  if(!result) {

    result = operate(&global, argc, argv);

#ifdef __SYMBIAN32__
    if(global.showerror)
      tool_pressanykey();
#endif


    main_free(&global);
  }

#ifdef __NOVELL_LIBC__
  if(getenv("_IN_NETWARE_BASH_") == NULL)
    tool_pressanykey();
#endif

#ifdef __VMS
  vms_special_exit(res, vms_show);
#else
  return (int)result;
#endif
}
