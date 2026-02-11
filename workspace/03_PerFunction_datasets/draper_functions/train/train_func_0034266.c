eel_editable_label_set_text (EelEditableLabel *label,
			     const gchar *str)
{
  GtkEditable *editable;
  int tmp_pos;

  g_return_if_fail (EEL_IS_EDITABLE_LABEL (label));
  g_return_if_fail (str != NULL);

  if (strcmp (label->text, str) == 0)
    return;

  editable = GTK_EDITABLE (label);
  gtk_editable_delete_text (editable, 0, -1);
  tmp_pos = 0;
  gtk_editable_insert_text (editable, str, strlen (str), &tmp_pos);
}
