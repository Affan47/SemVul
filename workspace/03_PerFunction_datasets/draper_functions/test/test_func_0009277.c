check_default (AudioConvertCtx * ctx, AudioConvertFmt * fmt)
{
  if (!DOUBLE_INTERMEDIATE_FORMAT (ctx)) {
    return (fmt->width == 32 && fmt->depth == 32 &&
        fmt->endianness == G_BYTE_ORDER && fmt->sign == TRUE);
  } else {
    return (fmt->width == 64 && fmt->endianness == G_BYTE_ORDER);
  }
}
