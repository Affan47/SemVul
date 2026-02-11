accept_connection_bottom (assuan_context_t ctx)
{
  assuan_fd_t fd = ctx->connected_fd;

  ctx->peercred_valid = 0;
#ifdef HAVE_SO_PEERCRED
  {
    struct ucred cr;
    socklen_t cl = sizeof cr;

    if ( !getsockopt (fd, SOL_SOCKET, SO_PEERCRED, &cr, &cl))
      {
         ctx->peercred.pid = cr.pid;
         ctx->peercred.uid = cr.uid;
         ctx->peercred.gid = cr.gid;
         ctx->peercred_valid = 1;


         if (cr.pid != ASSUAN_INVALID_PID && cr.pid)
           ctx->pid = cr.pid;
      }
  }
#endif

  ctx->inbound.fd = fd;
  ctx->inbound.eof = 0;
  ctx->inbound.linelen = 0;
  ctx->inbound.attic.linelen = 0;
  ctx->inbound.attic.pending = 0;

  ctx->outbound.fd = fd;
  ctx->outbound.data.linelen = 0;
  ctx->outbound.data.error = 0;

  ctx->flags.confidential = 0;

  return 0;
}
