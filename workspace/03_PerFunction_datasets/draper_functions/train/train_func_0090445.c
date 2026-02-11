rmt_close__ (int handle)
{
  long int status;

  if (do_command (handle, "C\n") == -1)
    return -1;

  status = get_status (handle);
  _rmt_shutdown (handle, errno);
  return status;
}
