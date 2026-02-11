_shell_remove_all_custom_widgets (GnomeControlCenterPrivate *priv)
{
  GtkBox *box;
  GtkWidget *widget;
  guint i;


  box = GTK_BOX (W (priv->builder, "topright"));
  for (i = 0; i < priv->custom_widgets->len; i++)
    {
        widget = g_ptr_array_index (priv->custom_widgets, i);
        gtk_container_remove (GTK_CONTAINER (box), widget);
    }
  g_ptr_array_set_size (priv->custom_widgets, 0);
}
