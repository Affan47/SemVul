_ecore_poll_events_from_fdh(Ecore_Fd_Handler *fdh)
{
   int events = 0;
   if (fdh->flags & ECORE_FD_READ) events |= EPOLLIN;
   if (fdh->flags & ECORE_FD_WRITE) events |= EPOLLOUT;
   if (fdh->flags & ECORE_FD_ERROR) events |= EPOLLERR | EPOLLPRI;
   return events;
}
