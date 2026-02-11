handle_input (ACE_HANDLE)
{
  ACE_TRACE (ACE_TEXT ("ACE_TS_Server_Handler::handle_input"));

  if (this->recv_request () == -1)
    return -1;
  else
    return this->dispatch ();
}
