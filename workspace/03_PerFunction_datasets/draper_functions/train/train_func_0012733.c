audio_convert_get_sizes (AudioConvertCtx * ctx, gint samples, gint * srcsize,
    gint * dstsize)
{
  g_return_val_if_fail (ctx != NULL, FALSE);

  if (srcsize)
    *srcsize = samples * ctx->in.unit_size;
  if (dstsize)
    *dstsize = samples * ctx->out.unit_size;

  return TRUE;
}
