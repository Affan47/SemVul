watchdog_thread(void* arg)
{
  sigset_t signalset;

  int signalno;
  bool exiting = false;


  while (!exiting)
  {
	  sigemptyset(&signalset);


	  sigaddset(&signalset, SIGTERM);
	  sigaddset(&signalset, SIGINT);
	  sigaddset(&signalset, SIGHUP);
	  sigaddset(&signalset, SIGPIPE);


	  sigwait(&signalset, &signalno);


	  if (signalno == SIGHUP) {


		  exiting = true;
	  }
	  else {
		  exiting = true;
	  }
  }

  ::wxGetApp().getMainwin()->Close(TRUE);

  ::wxGetApp().ExitMainLoop();
  printf ("bye bye, hope you had fun...\n");


  return(0);
}
