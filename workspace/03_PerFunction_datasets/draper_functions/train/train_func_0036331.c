mag_pix()
{
  GdkPixbuf  **src_p;
  src_p=which_pixbuf_is_visible(mag_source);

  mag_ox=(-(mag_x)*mag_zoom+mag_width/2);
  mag_oy=(-(mag_y)*mag_zoom+mag_height/2);

  if(!*src_p) return;
  gdk_pixbuf_scale(*src_p,
		   mag_pixbuf,
		   0,0,
		   mag_width,
		   mag_height,
		   mag_ox,
		   mag_oy,
		   mag_zoom,
		   mag_zoom,
		   GDK_INTERP_BILINEAR);
  mag_draw();
}
