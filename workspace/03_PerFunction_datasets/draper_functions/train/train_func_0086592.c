handle_close (ACE_HANDLE,
                                    ACE_Reactor_Mask mask)
{
  ACE_TRACE (ACE_TEXT ("ACE_TS_Clerk_Handler::handle_close"));
  ACE_UNUSED_ARG (mask);

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) shutting down on handle %d\n"),
              this->get_handle ()));

  return this->reinitiate_connection ();
}
