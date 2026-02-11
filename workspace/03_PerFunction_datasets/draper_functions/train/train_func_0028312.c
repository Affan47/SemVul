flGetOutline(FLfontNumber fn, GLuint c)
{
  TRACE(("flGetOutline: fn=%d, c='%c'(%u)\n", fn, c, c));
  return _flGetOutline(flGetFontInfo(fn), c);
}
