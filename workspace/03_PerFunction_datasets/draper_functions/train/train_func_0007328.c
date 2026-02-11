analogtv_font_set_char(analogtv_font *f, int c, char *s)
{
  int value,x,y;

  if (c<0 || c>=256) return;

  for (y=0; y<f->char_h; y++) {
    for (x=0; x<f->char_w; x++) {
      if (!*s) return;
      value=(*s==' ') ? 0 : 1;
      analogtv_font_set_pixel(f, c, x, y, value);
      s++;
    }
  }
}
