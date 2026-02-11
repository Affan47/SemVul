set_text_to_entry (GdictSourceDialog *dialog,
		   const gchar       *entry_name,
		   const gchar       *text)
{
  GtkWidget *entry;

  entry = GTK_WIDGET (gtk_builder_get_object (dialog->builder, entry_name));
  if (!entry)
    return;

  gtk_entry_set_text (GTK_ENTRY (entry), text);
}
