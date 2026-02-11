work_pending_i (ACE_Time_Value * max_wait_time)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::work_pending_i");

  if (this->deactivated_)
    return 0;

#if defined (ACE_HAS_EVENT_POLL)
  if (this->event_.data.fd != ACE_INVALID_HANDLE)
#else
  if (this->start_pfds_ != this->end_pfds_)
#endif
    return 1;


  ACE_Time_Value timer_buf (0);
  ACE_Time_Value *this_timeout =
    this->timer_queue_->calculate_timeout (max_wait_time, &timer_buf);


  int const timers_pending =
    ((this_timeout != 0 && max_wait_time == 0)
     || (this_timeout != 0 && max_wait_time != 0
         && *this_timeout != *max_wait_time) ? 1 : 0);

  long const timeout =
    (this_timeout == 0
     ? -1
     : static_cast<long> (this_timeout->msec ()));

#if defined (ACE_HAS_EVENT_POLL)


  {
    ACE_GUARD_RETURN (ACE_SYNCH_MUTEX, grd, this->to_be_resumed_lock_, -1);
    this->epoll_wait_in_progress_ = true;
    for (Resume_Map::iterator i = this->to_be_resumed_.begin ();
         i != this->to_be_resumed_.end ();
         ++i)
      {


        Event_Tuple *info = this->handler_rep_.find (i->first);
        if (info != 0 && info->event_handler == i->second)
          {
            this->resume_handler_i (i->first);
          }
      }
    this->to_be_resumed_.clear ();
  }


  int const nfds = ::epoll_wait (this->poll_fd_,
                                 &this->event_,
                                 1,
                                 static_cast<int> (timeout));


  this->epoll_wait_in_progress_ = false;

#else

  struct dvpoll dvp;

  dvp.dp_fds = this->dp_fds_;
  dvp.dp_nfds = this->handler_rep_.size ();
  dvp.dp_timeout = timeout;


  int const nfds = ACE_OS::ioctl (this->poll_fd_, DP_POLL, &dvp);


  this->start_pfds_ = dvp.dp_fds;


  if (nfds > -1)
    this->end_pfds_ = this->start_pfds_ + nfds;
#endif


  return (nfds == 0 && timers_pending != 0 ? 1 : nfds);
}
