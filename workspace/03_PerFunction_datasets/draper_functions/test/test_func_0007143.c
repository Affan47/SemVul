gm_powermeter_redraw (GmPowermeter* powermeter)
{
  guint calculated_index = 0;

  g_return_if_fail (GM_IS_POWERMETER (powermeter));

  calculated_index =
    gm_powermeter_get_index_by_level (powermeter->priv->iconset->max_index,
				      powermeter->priv->level);

  gtk_image_set_from_pixbuf (GTK_IMAGE (powermeter),
			     powermeter->priv->iconset->iconv [calculated_index]);
}
