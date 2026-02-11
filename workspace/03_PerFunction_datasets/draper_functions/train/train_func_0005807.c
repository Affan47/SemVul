accept_connection (assuan_context_t ctx)
{
  assuan_fd_t fd;
  struct sockaddr_un clnt_addr;
  socklen_t len = sizeof clnt_addr;

  fd = SOCKET2HANDLE(accept (HANDLE2SOCKET(ctx->listen_fd),
                             (struct sockaddr*)&clnt_addr, &len ));
  if (fd == ASSUAN_INVALID_FD)
    {
      return _assuan_error (ctx, gpg_err_code_from_syserror ());
    }
  if (_assuan_sock_check_nonce (ctx, fd, &ctx->listen_nonce))
    {
      _assuan_close (ctx, fd);
      return _assuan_error (ctx, GPG_ERR_ASS_ACCEPT_FAILED);
    }

  ctx->connected_fd = fd;
  return accept_connection_bottom (ctx);
}
