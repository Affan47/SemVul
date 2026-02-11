nxt_display_polygon(nxt_display_t *display,nxt_display_color_t color,int points,...) {
  va_list args;
  int x,y,xlast,ylast,x1,y1;

  if (points<2) return;

  va_start(args,points);

  x1 = xlast = va_arg(args,int);
  y1 = ylast = va_arg(args,int);

  for (;points>1;points--) {
    x = va_arg(args,int);
    y = va_arg(args,int);

    nxt_display_line(display,color,xlast,ylast,x,y);

    xlast = x;
    ylast = y;
  }

  nxt_display_line(display,color,xlast,ylast,x1,y1);

  va_end(args);
}
