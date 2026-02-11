assuan_socket_connect (assuan_context_t ctx, const char *name,
		       pid_t server_pid, unsigned int flags)
{
  gpg_error_t err;
  assuan_fd_t fd;
  struct sockaddr_un srvr_addr;
  size_t len;
  const char *s;

  TRACE2 (ctx, ASSUAN_LOG_CTX, "assuan_socket_connect", ctx,
	  "name=%s, flags=0x%x", name ? name : "(null)", flags);

  if (!ctx || !name)
    return _assuan_error (ctx, GPG_ERR_ASS_INV_VALUE);


  s = name;
  if (*s && s[1] == ':')
    s += 2;
  if (*s != DIRSEP_C && *s != '/')
    return _assuan_error (ctx, GPG_ERR_ASS_INV_VALUE);

  if (strlen (name)+1 >= sizeof srvr_addr.sun_path)
    return _assuan_error (ctx, GPG_ERR_ASS_INV_VALUE);

  fd = _assuan_sock_new (ctx, PF_LOCAL, SOCK_STREAM, 0);
  if (fd == ASSUAN_INVALID_FD)
    {
      TRACE1 (ctx, ASSUAN_LOG_SYSIO, "assuan_socket_connect_ext", ctx,
	      "can't create socket: %s", strerror (errno));

      return _assuan_error (ctx, GPG_ERR_ASS_GENERAL);
    }

  memset (&srvr_addr, 0, sizeof srvr_addr);
  srvr_addr.sun_family = AF_LOCAL;
  strncpy (srvr_addr.sun_path, name, sizeof (srvr_addr.sun_path) - 1);
  srvr_addr.sun_path[sizeof (srvr_addr.sun_path) - 1] = 0;
  len = SUN_LEN (&srvr_addr);

  if (_assuan_sock_connect (ctx, fd, (struct sockaddr *) &srvr_addr, len) == -1)
    {
      TRACE2 (ctx, ASSUAN_LOG_SYSIO, "assuan_socket_connect_ext", ctx,
	      "can't connect to `%s': %s\n", name, strerror (errno));

      _assuan_close (ctx, fd);
      return _assuan_error (ctx, GPG_ERR_ASS_CONNECT_FAILED);
    }

  ctx->engine.release = _assuan_client_release;
  ctx->engine.readfnc = _assuan_simple_read;
  ctx->engine.writefnc = _assuan_simple_write;
  ctx->engine.sendfd = NULL;
  ctx->engine.receivefd = NULL;
  ctx->finish_handler = _assuan_client_finish;
  ctx->inbound.fd = fd;
  ctx->outbound.fd = fd;
  ctx->max_accepts = -1;

  if (flags & ASSUAN_SOCKET_CONNECT_FDPASSING)
    _assuan_init_uds_io (ctx);


  {
    assuan_response_t response;
    int off;

    err = _assuan_read_from_server (ctx, &response, &off);
    if (err)
      TRACE1 (ctx, ASSUAN_LOG_SYSIO, "assuan_socket_connect_ext", ctx,
	      "can't connect to server: %s\n", gpg_strerror (err));
    else if (response != ASSUAN_RESPONSE_OK)
      {
	char *sname = _assuan_encode_c_string (ctx, ctx->inbound.line);
	if (sname)
	  {
	    TRACE1 (ctx, ASSUAN_LOG_SYSIO, "assuan_socket_connect_ext", ctx,
		    "can't connect to server: %s", sname);
	    _assuan_free (ctx, sname);
	  }
	err = _assuan_error (ctx, GPG_ERR_ASS_CONNECT_FAILED);
      }
  }

  if (err)
    _assuan_reset (ctx);

  return err;
}
