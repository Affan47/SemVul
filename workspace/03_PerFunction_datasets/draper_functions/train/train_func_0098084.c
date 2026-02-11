gtk_video_reshow (GtkVideo *gtv)
{
  if (gtv && GTK_IS_VIDEO (gtv))
  {
    gtv->priv->block_next_scale_change = TRUE;
    gtk_widget_show (&gtv->widget);
    gtk_widget_set_size_request (&gtv->widget,
				 gtv->priv->size.width, gtv->priv->size.height);
    gdk_flush ();
    gtv_unblock_timeout (gtv);
    gtk_video_allow_shrink (gtv);
  }
}
