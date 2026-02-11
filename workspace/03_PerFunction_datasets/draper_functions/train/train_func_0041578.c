gst_audio_quantize_free_noise_shaping (AudioConvertCtx * ctx)
{
  switch (ctx->ns) {
    case NOISE_SHAPING_HIGH:
    case NOISE_SHAPING_MEDIUM:
    case NOISE_SHAPING_SIMPLE:
    case NOISE_SHAPING_ERROR_FEEDBACK:
    case NOISE_SHAPING_NONE:
    default:
      break;
  }

  g_free (ctx->error_buf);
  ctx->error_buf = NULL;
  return;
}
