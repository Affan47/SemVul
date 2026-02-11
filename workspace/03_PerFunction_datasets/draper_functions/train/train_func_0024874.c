dest_size_cb (void *gv_gen,
			  int video_width, int video_height,
			  double video_pixel_aspect,
			  int *dest_width, int *dest_height,
			  double *dest_pixel_aspect)
{
  GtkVideo            *gv = (GtkVideo *) gv_gen;
  gtk_video_private_t *priv = gv->priv;

  if (is_fullscreen (priv))
  {
    *dest_width  = priv->fullscreen.width;
    *dest_height = priv->fullscreen.height;
  }
  else
  {
    *dest_width  = gv->widget.allocation.width;
    *dest_height = gv->widget.allocation.height;
  }

  *dest_pixel_aspect = priv->display_ratio;
}
