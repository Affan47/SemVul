glade_base_editor_set_show_signal_editor (GladeBaseEditor * editor,
                                          gboolean val)
{
  g_return_if_fail (GLADE_IS_BASE_EDITOR (editor));

  if (val)
    gtk_widget_show (GTK_WIDGET (editor->priv->signal_editor));
  else
    gtk_widget_hide (GTK_WIDGET (editor->priv->signal_editor));
}
