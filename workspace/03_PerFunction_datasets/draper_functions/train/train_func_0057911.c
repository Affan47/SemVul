install_ctx_free (InstallCtx *ctx)
{
  g_free (ctx->packages);
  g_free (ctx->options);
  g_object_unref (ctx->result);
  g_slice_free (InstallCtx, ctx);
}
