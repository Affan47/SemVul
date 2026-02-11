clear_dispatch_mask (ACE_HANDLE handle,
                                              ACE_Reactor_Mask mask)
{
  ACE_TRACE ("ACE_Select_Reactor_Impl::clear_dispatch_mask");


  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::READ_MASK) ||
      ACE_BIT_ENABLED (mask, ACE_Event_Handler::ACCEPT_MASK))
    {
      this->dispatch_set_.rd_mask_.clr_bit (handle);
    }
  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::WRITE_MASK))
    {
      this->dispatch_set_.wr_mask_.clr_bit (handle);
    }
  if (ACE_BIT_ENABLED (mask, ACE_Event_Handler::EXCEPT_MASK))
    {
      this->dispatch_set_.ex_mask_.clr_bit (handle);
    }


  this->state_changed_ = true;
}
