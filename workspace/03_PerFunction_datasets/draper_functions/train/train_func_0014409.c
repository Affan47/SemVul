set_window_xid (gpointer data, gpointer user_data)
{
  GstXOverlay *xov = GST_X_OVERLAY (data);
  struct xid_data *xiddata = (struct xid_data *) user_data;

  if (GST_ELEMENT_CAST(xov) == xiddata->src) {
    gst_x_overlay_set_xwindow_id (xov, xiddata->window_id);
    xiddata->found = TRUE;
  }
}
