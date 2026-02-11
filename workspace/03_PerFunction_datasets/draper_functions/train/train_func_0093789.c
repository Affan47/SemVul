My_XNextEvent(Display *dpy, XEvent *event)
{
  fd_set in_fdset;
  static int miss_counter = 0;

  if(FPending(dpy))
  {
    FNextEvent(dpy,event);
    return 1;
  }

  FD_ZERO(&in_fdset);
  FD_SET(x_fd,&in_fdset);
  FD_SET(fd[1],&in_fdset);

  select( fd_width, SELECT_FD_SET_CAST &in_fdset, 0, 0, NULL );


  if(FD_ISSET(x_fd, &in_fdset))
  {
    if(FPending(dpy))
    {
      FNextEvent(dpy,event);
      miss_counter = 0;
      return 1;
    }
    else
      miss_counter++;
    if(miss_counter > 100)
      DeadPipe(0);
  }

  if(FD_ISSET(fd[1], &in_fdset))
  {
    FvwmPacket* packet = ReadFvwmPacket(fd[1]);
    if ( packet == NULL )
      DeadPipe(0);
    else
      process_message( packet->type, packet->body );
  }
  return 0;
}
