main(int argc, char **argv)
{
  char *display_name = NULL;

  module = ParseModuleArgs(argc,argv,0);
  if (module == NULL)
  {
    fprintf(stderr,"FvwmSave Version %s should only be executed by fvwm!\n",
            VERSION);
    exit(1);
  }


  if (!(dpy = XOpenDisplay(display_name)))
    {
      fprintf(stderr,"%s: can't open display %s", module->name,
	      XDisplayName(display_name));
      exit (1);
    }
  screen= DefaultScreen(dpy);
  ScreenHeight = DisplayHeight(dpy,screen);
  ScreenWidth = DisplayWidth(dpy,screen);


  signal (SIGPIPE, DeadPipe);

  fd[0] = module->to_fvwm;
  fd[1] = module->from_fvwm;


  SendInfo(fd,"Send_WindowList",0);


  SendFinishedStartupNotification(fd);

  Loop(fd);
  return 0;
}
