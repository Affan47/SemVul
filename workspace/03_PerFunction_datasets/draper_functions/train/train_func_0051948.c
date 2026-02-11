shared_accept_finish (ACE_SOCK_SEQPACK_Association new_association,
                                         int in_blocking_mode,
                                         bool reset_new_handle) const
{
  ACE_TRACE ("ACE_SOCK_SEQPACK_Acceptor::shared_accept_finish ()");

  ACE_HANDLE new_handle = new_association.get_handle ();


  if (in_blocking_mode)
    {

      ACE_Errno_Guard error (errno);


      ACE::clr_flags (this->get_handle (),
                      ACE_NONBLOCK);
      ACE::clr_flags (new_handle,
                      ACE_NONBLOCK);
    }

#if defined (ACE_HAS_WINSOCK2) && (ACE_HAS_WINSOCK2 != 0)
  if (reset_new_handle)

    ::WSAEventSelect ((SOCKET) new_handle, 0, 0);
#else
  ACE_UNUSED_ARG (reset_new_handle);
#endif

  return new_handle == ACE_INVALID_HANDLE ? -1 : 0;
}
