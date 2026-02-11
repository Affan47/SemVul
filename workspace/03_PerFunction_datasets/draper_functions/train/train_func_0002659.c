uds_sendfd (assuan_context_t ctx, assuan_fd_t fd)
{
#ifdef USE_DESCRIPTOR_PASSING
  struct msghdr msg;
  struct iovec iovec;
  union {
    struct cmsghdr cm;
    char control[CMSG_SPACE(sizeof (int))];
  } control_u;
  struct cmsghdr *cmptr;
  int len;
  char buffer[80];


  snprintf (buffer, sizeof(buffer)-1, "# descriptor %d is in flight\n", fd);
  buffer[sizeof(buffer)-1] = 0;

  memset (&msg, 0, sizeof (msg));

  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iovlen = 1;
  msg.msg_iov = &iovec;
  iovec.iov_base = buffer;
  iovec.iov_len = strlen (buffer);

  msg.msg_control = control_u.control;
  msg.msg_controllen = sizeof (control_u.control);
  cmptr = CMSG_FIRSTHDR (&msg);
  cmptr->cmsg_len = CMSG_LEN(sizeof(int));
  cmptr->cmsg_level = SOL_SOCKET;
  cmptr->cmsg_type = SCM_RIGHTS;
  *((int*)CMSG_DATA (cmptr)) = fd;

  len = _assuan_sendmsg (ctx, ctx->outbound.fd, &msg, 0);
  if (len < 0)
    {
      int saved_errno = errno;
      TRACE1 (ctx, ASSUAN_LOG_SYSIO, "uds_sendfd", ctx,
	      "uds_sendfd: %s", strerror (errno));
      errno = saved_errno;
      return _assuan_error (ctx, gpg_err_code_from_syserror ());
    }
  else
    return 0;
#else
  return _assuan_error (ctx, GPG_ERR_NOT_IMPLEMENTED);
#endif
}
