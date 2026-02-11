register_notifier (ACE_Reactor *r)
{
  if (r == 0)
    return;
  if (this->notifier_ == 0)
    {
      ACE_NEW (this->notifier_,ACE::HTBP::Notifier(this));
    }
  else
    {
      if (notifier_->get_handle() == ACE_INVALID_HANDLE)
        {
          delete this->notifier_;
          ACE_NEW (this->notifier_,ACE::HTBP::Notifier(this));
        }
    }

  r->register_handler(notifier_,ACE_Event_Handler::READ_MASK);
}
