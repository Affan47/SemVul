c565_converter(const uchar *from, uchar *to, int w, int delta) {
  OUTTYPE *t = (OUTTYPE *)to;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    t = t+(w-1)*OUTSIZE;
    d = -delta;
    td = -OUTSIZE;
  } else {
    dir = 1;
    d = delta;
    td = OUTSIZE;
  }
  int r=ri, g=gi, b=bi;
  for (; w--; from += d, t += td) {
    r = (r&7)+from[0]; if (r>255) r = 255;
    g = (g&3)+from[1]; if (g>255) g = 255;
    b = (b&7)+from[2]; if (b>255) b = 255;
    OUTASSIGN(((r&0xf8)<<8) + ((g&0xfc)<<3) + (b>>3));
  }
  ri = r; gi = g; bi = b;
}
