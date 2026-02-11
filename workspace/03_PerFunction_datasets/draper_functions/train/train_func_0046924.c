set_current_actor (BaconVideoWidget *bvw)
{
  gboolean draw_logo;

  if (bvw->priv->stage == NULL)
    return;


  draw_logo = bvw->priv->media_has_audio &&
      !bvw->priv->media_has_video && (!bvw->priv->show_vfx || bvw->priv->cover_pixbuf);

  if (bvw->priv->logo_mode || draw_logo) {
    const GdkPixbuf *pixbuf;

    pixbuf = bvw_get_logo_pixbuf (bvw);
    if (pixbuf != NULL) {
      gboolean ret;
      GError *err = NULL;

      ret = clutter_texture_set_from_rgb_data (CLUTTER_TEXTURE (bvw->priv->logo),
					       gdk_pixbuf_get_pixels (pixbuf),
					       gdk_pixbuf_get_has_alpha (pixbuf),
					       gdk_pixbuf_get_width (pixbuf),
					       gdk_pixbuf_get_height (pixbuf),
					       gdk_pixbuf_get_rowstride (pixbuf),
					       gdk_pixbuf_get_has_alpha (pixbuf) ? 4 : 3,
					       CLUTTER_TEXTURE_NONE, &err);
      if (ret == FALSE) {
	g_message ("clutter_texture_set_from_rgb_data failed %s", err->message);
	g_error_free (err);
      } else {
	clutter_actor_show (CLUTTER_ACTOR (bvw->priv->logo_frame));
	clutter_actor_hide (CLUTTER_ACTOR (bvw->priv->frame));
	return;
      }
    }
  }

  clutter_actor_show (CLUTTER_ACTOR (bvw->priv->frame));
  clutter_actor_hide (CLUTTER_ACTOR (bvw->priv->logo_frame));
}
