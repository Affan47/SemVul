st_adjustment_set_page_increment (StAdjustment *adjustment,
                                  gdouble       page)
{
  StAdjustmentPrivate *priv = adjustment->priv;

  if (priv->page_increment != page)
    {
      priv->page_increment = page;

      g_signal_emit (adjustment, signals[CHANGED], 0);

      g_object_notify (G_OBJECT (adjustment), "page-increment");

      return TRUE;
    }

  return FALSE;
}
