_set_sunbmc_ctx_errnum_by_errno (ipmi_sunbmc_ctx_t ctx, int _errno)
{
  if (!ctx || ctx->magic != IPMI_SUNBMC_CTX_MAGIC)
    return;

  if (_errno == 0)
    ctx->errnum = IPMI_SUNBMC_ERR_SUCCESS;
  else if (_errno == EPERM)
    ctx->errnum = IPMI_SUNBMC_ERR_PERMISSION;
  else if (_errno == EACCES)
    ctx->errnum = IPMI_SUNBMC_ERR_PERMISSION;
  else if (_errno == ENOENT)
    ctx->errnum = IPMI_SUNBMC_ERR_DEVICE_NOT_FOUND;
  else if (_errno == ENOTDIR)
    ctx->errnum = IPMI_SUNBMC_ERR_DEVICE_NOT_FOUND;
  else if (_errno == ENAMETOOLONG)
    ctx->errnum = IPMI_SUNBMC_ERR_DEVICE_NOT_FOUND;
  else if (_errno == ENOMEM)
    ctx->errnum = IPMI_SUNBMC_ERR_OUT_OF_MEMORY;
  else if (_errno == ETIMEDOUT)
    ctx->errnum = IPMI_SUNBMC_ERR_DRIVER_TIMEOUT;
  else
    ctx->errnum = IPMI_SUNBMC_ERR_SYSTEM_ERROR;
}
