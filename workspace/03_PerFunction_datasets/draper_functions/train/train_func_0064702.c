code_relative_mark_size(GBitmap &bm, int cw, int ch, int border)
{
  int xdiff=CodeNum(BIGNEGATIVE, BIGPOSITIVE, rel_size_x);
  int ydiff=CodeNum(BIGNEGATIVE, BIGPOSITIVE, rel_size_y);
  int xsize = cw + xdiff;
  int ysize = ch + ydiff;
  if ((xsize!=(unsigned short)xsize) || (ysize!=(unsigned short)ysize))
    G_THROW( ERR_MSG("JB2Image.bad_number") );
  bm.init(ysize, xsize, border);
}
