reactor_mask_to_poll_event (ACE_Reactor_Mask mask)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::reactor_mask_to_poll_event");

  if (mask == ACE_Event_Handler::NULL_MASK)

#if defined (ACE_HAS_EVENT_POLL)
    return EPOLL_CTL_DEL;
#else
    return POLLREMOVE;
#endif

  short events = 0;


  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::READ_MASK)
      || ACE_BIT_ENABLED (mask, ACE_Event_Handler::ACCEPT_MASK)
      || ACE_BIT_ENABLED (mask, ACE_Event_Handler::CONNECT_MASK))
    {
#if defined (ACE_HAS_EVENT_POLL)
      ACE_SET_BITS (events, EPOLLIN);
#else
      ACE_SET_BITS (events, POLLIN);
#endif
    }


  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::WRITE_MASK)
      || ACE_BIT_ENABLED (mask, ACE_Event_Handler::CONNECT_MASK))
    {
#if defined (ACE_HAS_EVENT_POLL)
      ACE_SET_BITS (events, EPOLLOUT);
#else
      ACE_SET_BITS (events, POLLOUT);
#endif
    }


  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::EXCEPT_MASK))
    {
#if defined (ACE_HAS_EVENT_POLL)
      ACE_SET_BITS (events, EPOLLPRI);
#else
      ACE_SET_BITS (events, POLLPRI);
#endif
    }

  return events;
}
