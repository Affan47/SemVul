recv_buf (ACE_MEM_SAP_Node *&buf,
                               int flags,
                               const ACE_Time_Value *timeout)
{
  ACE_TRACE ("ACE_Reactive_MEM_IO::recv_buf");

  if (this->shm_malloc_ == 0 || this->handle_ == ACE_INVALID_HANDLE)
    return -1;

  ACE_OFF_T new_offset = 0;
  ssize_t retv = ACE::recv (this->handle_,
                            (char *) &new_offset,
                            sizeof (ACE_OFF_T),
                            flags,
                            timeout);

  if (retv == 0)
    {

      buf = 0;
      return 0;
    }
  else if (retv != static_cast <ssize_t> (sizeof (ACE_OFF_T)))
    {

      buf = 0;
      return -1;
    }

  return this->get_buf_len (new_offset, buf);
}
