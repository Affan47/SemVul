varpanel_label_set (gint j, GGobiData * d)
{
  GtkWidget *label = varpanel_widget_get_nth (VARSEL_LABEL, j, d);

  GtkWidget *labelw;

  if (!label || !GTK_IS_BIN (label))
    return;

  labelw = GTK_BIN (label)->child;

  if (!labelw)
    return;

  gtk_misc_set_alignment (GTK_MISC (labelw), 0, .5);
  gtk_label_set_text (GTK_LABEL (labelw), ggobi_data_get_col_name(d, j));
}
