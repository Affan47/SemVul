ipmi_interpret_ctx_create (void)
{
  struct ipmi_interpret_ctx *ctx = NULL;

  if (!(ctx = (ipmi_interpret_ctx_t)malloc (sizeof (struct ipmi_interpret_ctx))))
    {
      ERRNO_TRACE (errno);
      return (NULL);
    }
  memset (ctx, '\0', sizeof (struct ipmi_interpret_ctx));
  ctx->magic = IPMI_INTERPRET_CTX_MAGIC;
  ctx->flags = IPMI_INTERPRET_FLAGS_DEFAULT;

  if (!(ctx->sel_parse_ctx = ipmi_sel_parse_ctx_create (NULL, NULL)))
    {
      ERRNO_TRACE (errno);
      goto cleanup;
    }

  if (ipmi_interpret_sel_init (ctx) < 0)
    goto cleanup;

  if (ipmi_interpret_sensor_init (ctx) < 0)
    goto cleanup;

  return (ctx);

 cleanup:
  if (ctx)
    {
      ipmi_sel_parse_ctx_destroy (ctx->sel_parse_ctx);
      ipmi_interpret_sel_destroy (ctx);
      ipmi_interpret_sensor_destroy (ctx);
      free (ctx);
    }
  return (NULL);
}
