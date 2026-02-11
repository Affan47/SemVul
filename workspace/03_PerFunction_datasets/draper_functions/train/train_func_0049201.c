ipmi_kcs_ctx_create (void)
{
  ipmi_kcs_ctx_t ctx = NULL;

  if (!(ctx = (ipmi_kcs_ctx_t)malloc (sizeof (struct ipmi_kcs_ctx))))
    {
      ERRNO_TRACE (errno);
      return (NULL);
    }
  memset (ctx, '\0', sizeof (struct ipmi_kcs_ctx));

  ctx->magic = IPMI_KCS_CTX_MAGIC;
  ctx->driver_address = IPMI_KCS_SMS_IO_BASE_DEFAULT;
  ctx->register_spacing = IPMI_KCS_SMS_REGISTER_SPACING_DEFAULT;
  ctx->flags = IPMI_KCS_FLAGS_DEFAULT;
  ctx->poll_interval = IPMI_KCS_SLEEP_USECS;
  ctx->io_init = 0;

  if ((ctx->semid = ipmi_mutex_init ()) < 0)
    {
      ERRNO_TRACE (errno);
      goto cleanup;
    }
  ctx->errnum = IPMI_KCS_ERR_SUCCESS;
  return (ctx);

 cleanup:
  free (ctx);
  return (NULL);
}
