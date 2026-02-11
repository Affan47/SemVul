_glade_design_layout_set_highlight (GladeDesignLayout *layout,
                                    GladeWidget       *drag)
{
  GladeDesignLayoutPrivate *priv = layout->priv;

  g_clear_object (&priv->drag_dest);

  if (drag)
    priv->drag_dest = g_object_ref (drag);

  gtk_widget_queue_draw (GTK_WIDGET (layout));
}
