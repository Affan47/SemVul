gst_audio_quantize_setup_quantize_func (AudioConvertCtx * ctx)
{
  gint index = 0;

  if (!ctx->out.is_int) {
    ctx->quantize = NULL;
    return;
  }

  if (ctx->ns == NOISE_SHAPING_NONE) {
    index += ctx->dither;
    index += (ctx->out.sign) ? 0 : 4;
  } else {
    index += 8 + (4 * ctx->dither);
    index += ctx->ns - 1;
  }

  ctx->quantize = quantize_funcs[index];
}
