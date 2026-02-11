disp_label_edit(char *str)
{
  if (!label_edit)
    return;

  show_hide_label_edit();

  gtk_label_set_markup(GTK_LABEL(label_edit), str);
}
