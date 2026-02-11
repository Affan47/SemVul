fill(gColor col)
{
  if (_type == SERVER)
  {
  	gt_pixmap_fill(pic, col, NULL);
  }
  else if (_type == MEMORY)
  {
  	int r, g, b, a;
		union
		{
			char c[4];
			uint value;
		}
		color;

  	gt_color_to_rgba(col, &r, &g, &b, &a);

  	color.c[0] = a ^ 0xFF;
  	color.c[1] = b;
  	color.c[2] = g;
  	color.c[3] = r;

  	gdk_pixbuf_fill(img, color.value);
  }

  invalidate();
}
