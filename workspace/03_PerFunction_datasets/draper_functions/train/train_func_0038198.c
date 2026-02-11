FvwmErrorHandler(Display *dpy, XErrorEvent *event)
{
  extern int last_event_type;


  if((event->error_code == BadWindow)||(event->request_code == X_GetGeometry)||
     (event->error_code==BadDrawable)||(event->request_code==X_SetInputFocus)||
     (event->request_code==X_GrabButton)||
     (event->request_code==X_ChangeWindowAttributes)||
     (event->request_code == X_InstallColormap))
    return 0 ;


  fvwm_err("internal error",NULL,NULL,NULL);
  fprintf(stderr,"      Request %d, Error %d\n", event->request_code,
	  event->error_code);
  fprintf(stderr,"      EventType: %d",last_event_type);
  fprintf(stderr,"\n");
  return 0;
}
