eel_editable_label_accessible_copy_text   (AtkEditableText *text,
					   gint            start_pos,
					   gint            end_pos)
{
  GtkWidget *widget;
  EelEditableLabel *label;
  GtkEditable *editable;
  gchar *str;

  widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
  if (widget == NULL)

    return;

  label = EEL_EDITABLE_LABEL (widget);
  editable = GTK_EDITABLE (label);
  str = gtk_editable_get_chars (editable, start_pos, end_pos);
  gtk_clipboard_set_text (gtk_clipboard_get (GDK_NONE), str, -1);
}
