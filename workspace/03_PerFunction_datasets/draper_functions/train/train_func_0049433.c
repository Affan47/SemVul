dispatch_socket_event (ACE_EH_Dispatch_Info &dispatch_info)
{
  ACE_TRACE ("ACE_TP_Reactor::dispatch_socket_event");

  ACE_Event_Handler * const event_handler = dispatch_info.event_handler_;
  ACE_EH_PTMF const callback = dispatch_info.callback_;


  if (event_handler == 0)
    return -1;


  int status = 1;
  while (status > 0)
    status = (event_handler->*callback) (dispatch_info.handle_);


  return this->post_process_socket_event (dispatch_info, status);
}
