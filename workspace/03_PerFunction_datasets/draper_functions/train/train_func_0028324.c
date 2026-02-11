flGetCurrentFont(void)
{
  FLcontext ctx = current_context;
  FLfontNumber fn = ctx ? ctx->current_font : BAD_FONT_NUMBER;

  TRACE(("flGetCurrentFont: fn=%d\n", fn));

  return fn;
}
