glade_design_layout_remove (GtkContainer *container, GtkWidget *widget)
{
  GladeWidget *gchild;

  if ((gchild = glade_widget_get_from_gobject (G_OBJECT (widget))))
    {
      GladeDesignLayoutPrivate *priv = GLADE_DESIGN_LAYOUT_PRIVATE (container);

      g_signal_handlers_disconnect_by_func (gchild, on_glade_widget_name_notify,
                                            GLADE_DESIGN_LAYOUT (container));
      if (gchild == priv->gchild)
        priv->gchild = NULL;
    }

  GTK_CONTAINER_CLASS (glade_design_layout_parent_class)->remove (container, widget);
  gtk_widget_queue_draw (GTK_WIDGET (container));
}
