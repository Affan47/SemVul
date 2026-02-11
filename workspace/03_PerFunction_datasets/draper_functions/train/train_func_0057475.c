bind (
  ACE_HANDLE handle,
  ACE_Event_Handler *event_handler,
  ACE_Reactor_Mask mask)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::Handler_Repository::bind");

  if (event_handler == 0)
    return -1;

  if (handle == ACE_INVALID_HANDLE)
    handle = event_handler->get_handle ();

  if (this->invalid_handle (handle))
    return -1;

  this->handlers_[handle].event_handler = event_handler;
  this->handlers_[handle].mask = mask;
  event_handler->add_reference ();
  ++this->size_;

  return 0;
}
