matewnck_pager_set_orientation (MatewnckPager     *pager,
                            GtkOrientation orientation)
{
  GtkOrientation old_orientation;
  gboolean       old_orientation_is_valid;

  g_return_val_if_fail (MATEWNCK_IS_PAGER (pager), FALSE);

  if (pager->priv->orientation == orientation)
    return TRUE;

  old_orientation = pager->priv->orientation;
  old_orientation_is_valid = pager->priv->screen != NULL;

  pager->priv->orientation = orientation;

  if (matewnck_pager_set_layout_hint (pager))
    {
      gtk_widget_queue_resize (GTK_WIDGET (pager));
      return TRUE;
    }
  else
    {
      if (old_orientation_is_valid)
        pager->priv->orientation = old_orientation;
      return FALSE;
    }
}
