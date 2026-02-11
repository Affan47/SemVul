ShutdownX(void)
{
  int i;
  static XEvent event;
  fd_set in_fdset;
  extern int x_fd;
  Atom MyAtom;
  int NbEssai=0;
  struct timeval tv;

#ifdef DEBUG
  XSync(dpy,0);
#endif


  if (x11base->quitfunc != NULL)
    ExecBloc(x11base->quitfunc);

  if (is_dead_pipe)
    return;


  XUnmapWindow(dpy,x11base->win);
  XFlush(dpy);


  MyAtom = XInternAtom(dpy, x11base->TabScriptId[1], False);
  XSetSelectionOwner(dpy, MyAtom, x11base->root, CurrentTime);


  while(!isTerminated && (BuffSend.NbMsg > 0) && (NbEssai < 10000) )
  {
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&in_fdset);
    FD_SET(x_fd,&in_fdset);
    if ( fvwmSelect(x_fd+1, &in_fdset, NULL, NULL, &tv) > 0 )
    {
      if (FD_ISSET(x_fd, &in_fdset))
      {
	if (FCheckTypedEvent(dpy, SelectionRequest, &event))
	  SendMsgToScript(event);
	else
	  NbEssai++;
      }
    }
  }
  XFlush(dpy);


  for (i=0; i<nbobj; i++)
    tabxobj[i]->DestroyObj(tabxobj[i]);
  XFlush(dpy);
  fsm_close();
  sleep(2);
  XCloseDisplay(dpy);
}
