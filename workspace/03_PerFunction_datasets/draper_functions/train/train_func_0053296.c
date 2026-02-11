handle_timeout (const ACE_Time_Value &,
                                      const void *)
{
  ACE_TRACE (ACE_TEXT ("ACE_TS_Clerk_Handler::handle_timeout"));
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t) attempting to reconnect to server with timeout = %d\n"),
              this->timeout_));


  this->peer ().close ();

  return this->processor_->initiate_connection (this, ACE_Synch_Options::asynch);
}
