mask_ops_i (ACE_HANDLE handle,
                                  ACE_Reactor_Mask mask,
                                  int ops)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::mask_ops_i");

  Event_Tuple *info = this->handler_rep_.find (handle);
  if (info == 0)
    return -1;


  ACE_Sig_Guard sb;

  ACE_Reactor_Mask const old_mask = info->mask;
  ACE_Reactor_Mask new_mask = old_mask;


  switch (ops)
    {
    case ACE_Reactor::GET_MASK:


      return old_mask;

    case ACE_Reactor::CLR_MASK:
      ACE_CLR_BITS (new_mask, mask);
      break;

    case ACE_Reactor::SET_MASK:
      new_mask = mask;
      break;

    case ACE_Reactor::ADD_MASK:
      ACE_SET_BITS (new_mask, mask);
      break;

    default:
      return -1;
    }


  info->mask = new_mask;


  if (!info->suspended || (info->controlled && new_mask == 0))
    {

      short const events = this->reactor_mask_to_poll_event (new_mask);

#if defined (sun)


      struct pollfd pfd[2];

      pfd[0].fd      = handle;
      pfd[0].events  = POLLREMOVE;
      pfd[0].revents = 0;
      pfd[1].fd      = (events == POLLREMOVE ? ACE_INVALID_HANDLE : handle);
      pfd[1].events  = events;
      pfd[1].revents = 0;


      if (ACE_OS::write (this->poll_fd_,
                         pfd,
                         sizeof (pfd)) != sizeof (pfd))
        return -1;
#elif defined (ACE_HAS_EVENT_POLL)

      struct epoll_event epev;
      ACE_OS::memset (&epev, 0, sizeof (epev));
      int op;


      if (new_mask == 0)
        {
          op          = EPOLL_CTL_DEL;
          epev.events = 0;
        }
      else
        {
          op          = EPOLL_CTL_MOD;
          epev.events = events | EPOLLONESHOT;
        }

      epev.data.fd = handle;

      if (::epoll_ctl (this->poll_fd_, op, handle, &epev) == -1)
        {


          if (op == EPOLL_CTL_MOD && errno == ENOENT &&
              ::epoll_ctl (this->poll_fd_, EPOLL_CTL_ADD, handle, &epev) == -1)
            return -1;
        }
      info->controlled = (op != EPOLL_CTL_DEL);
#else
      pollfd pfd[1];

      pfd[0].fd      = handle;
      pfd[0].events  = events;
      pfd[0].revents = 0;


      if (ACE_OS::write (this->poll_fd_,
                         pfd,
                         sizeof (pfd)) != sizeof (pfd))
        return -1;
#endif
    }

  return old_mask;
}
