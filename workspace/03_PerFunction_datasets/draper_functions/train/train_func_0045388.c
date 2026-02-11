assuan_socket_connect_fd (assuan_context_t ctx, int fd, unsigned int flags)
{
  gpg_error_t err;

  if (!ctx || fd < 0)
    return GPG_ERR_INV_ARG;

  err = _assuan_connect_finalize(ctx, fd, flags);

  if (err)
    _assuan_reset (ctx);

  return err;
}
