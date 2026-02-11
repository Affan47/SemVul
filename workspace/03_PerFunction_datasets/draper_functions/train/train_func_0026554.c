populate_style_tag_table (LogviewWindow *logview)
{
  GtkTextTagTable *tag_table = logview->priv->tag_table;
  GtkTextTag *tag;
  GtkStyleContext *context;
  GdkRGBA rgba;

  tag = gtk_text_tag_table_lookup (tag_table, "gray");

  if (tag) {
    gtk_text_tag_table_remove (tag_table, tag);
  }

  tag = gtk_text_tag_new ("gray");

  context = gtk_widget_get_style_context (logview->priv->text_view);
  gtk_style_context_save (context);
  gtk_style_context_add_class (context, "dim-label");
  gtk_style_context_get_color (context, GTK_STATE_FLAG_NORMAL, &rgba);
  gtk_style_context_restore (context);

  g_object_set (tag, "foreground-rgba", &rgba, "foreground-set", TRUE, NULL);

  gtk_text_tag_table_add (tag_table, tag);
}
