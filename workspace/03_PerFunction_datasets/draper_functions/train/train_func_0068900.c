bit_ops (ACE_HANDLE handle,
                                  ACE_Reactor_Mask mask,
                                  ACE_Select_Reactor_Handle_Set &handle_set,
                                  int ops)
{
  ACE_TRACE ("ACE_Select_Reactor_Impl::bit_ops");
  if (this->handler_rep_.handle_in_range (handle) == 0)
    return -1;

#if !defined (ACE_WIN32)
  ACE_Sig_Guard sb (0,
                    this->mask_signals_);
#endif

  ACE_FDS_PTMF ptmf  = &ACE_Handle_Set::set_bit;
  u_long omask = ACE_Event_Handler::NULL_MASK;


  if (handle_set.rd_mask_.is_set (handle))
    ACE_SET_BITS (omask, ACE_Event_Handler::READ_MASK);
  if (handle_set.wr_mask_.is_set (handle))
    ACE_SET_BITS (omask, ACE_Event_Handler::WRITE_MASK);
  if (handle_set.ex_mask_.is_set (handle))
    ACE_SET_BITS (omask, ACE_Event_Handler::EXCEPT_MASK);

  switch (ops)
    {
    case ACE_Reactor::GET_MASK:


      break;
    case ACE_Reactor::CLR_MASK:
      ptmf = &ACE_Handle_Set::clr_bit;


      this->clear_dispatch_mask (handle, mask);

    case ACE_Reactor::SET_MASK:

    case ACE_Reactor::ADD_MASK:


      if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::READ_MASK)
          || ACE_BIT_ENABLED (mask, ACE_Event_Handler::ACCEPT_MASK)
          || ACE_BIT_ENABLED (mask, ACE_Event_Handler::CONNECT_MASK))
        {
          (handle_set.rd_mask_.*ptmf) (handle);
        }
      else if (ops == ACE_Reactor::SET_MASK)
        handle_set.rd_mask_.clr_bit (handle);


      if (ACE_BIT_ENABLED (mask,
                           ACE_Event_Handler::WRITE_MASK)
          || ACE_BIT_ENABLED (mask,
                              ACE_Event_Handler::CONNECT_MASK))
        {
          (handle_set.wr_mask_.*ptmf) (handle);
        }
      else if (ops == ACE_Reactor::SET_MASK)
        handle_set.wr_mask_.clr_bit (handle);


      if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::EXCEPT_MASK)
#if defined (ACE_WIN32)
          || ACE_BIT_ENABLED (mask, ACE_Event_Handler::CONNECT_MASK)
#endif
          )
        {
          (handle_set.ex_mask_.*ptmf) (handle);
        }
      else if (ops == ACE_Reactor::SET_MASK)
        handle_set.ex_mask_.clr_bit (handle);
      break;
    default:
      return -1;
    }
  return omask;
}
