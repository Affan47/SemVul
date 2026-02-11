iocop_device (const char *str)
{
  char *p;
  long opcode;
  off_t count;
  uintmax_t n;

  opcode = strtol (str, &p, 10);
  if (*p)
    {
      rmt_error_message (EINVAL, N_("Invalid operation code"));
      return;
    }
  str = rmt_read ();
  n = count = strtoumax (str, &p, 10);
  if (*p)
    {
      rmt_error_message (EINVAL, N_("Invalid byte count"));
      return;
    }

  if (n != count || errno == ERANGE)
    {
      rmt_error_message (EINVAL, N_("Byte count out of range"));
      return;
    }

#ifdef MTIOCTOP
  {
    struct mtop mtop;

    mtop.mt_count = count;
    if (mtop.mt_count != count)
      {
	rmt_error_message (EINVAL, N_("Byte count out of range"));
	return;
      }

    mtop.mt_op = opcode;
    if (ioctl (device_fd, MTIOCTOP, (char *) &mtop) < 0)
      rmt_error (errno);
    else
      rmt_reply (0);
  }
#else
  rmt_error_message (ENOSYS, N_("Operation not supported"));
#endif
}
