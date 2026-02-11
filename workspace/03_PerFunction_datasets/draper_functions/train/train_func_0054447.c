wnck_pager_get_request_mode (GtkWidget *widget)
{
  WnckPager *pager;

  pager = WNCK_PAGER (widget);

  if (pager->priv->orientation == GTK_ORIENTATION_VERTICAL)
    return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;
  else
    return GTK_SIZE_REQUEST_WIDTH_FOR_HEIGHT;
}
