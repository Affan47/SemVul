ipmi_sunbmc_ctx_set_driver_device (ipmi_sunbmc_ctx_t ctx, const char *driver_device)
{
  if (!ctx || ctx->magic != IPMI_SUNBMC_CTX_MAGIC)
    {
      ERR_TRACE (ipmi_sunbmc_ctx_errormsg (ctx), ipmi_sunbmc_ctx_errnum (ctx));
      return (-1);
    }

  if (!driver_device)
    {
      SUNBMC_SET_ERRNUM (ctx, IPMI_SUNBMC_ERR_PARAMETERS);
      return (-1);
    }

  free (ctx->driver_device);
  ctx->driver_device = NULL;

  if (!(ctx->driver_device = strdup (driver_device)))
    {
      SUNBMC_SET_ERRNUM (ctx, IPMI_SUNBMC_ERR_OUT_OF_MEMORY);
      return (-1);
    }

  ctx->errnum = IPMI_SUNBMC_ERR_SUCCESS;
  return (0);
}
