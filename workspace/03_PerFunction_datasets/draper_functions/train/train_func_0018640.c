gtk_sheet_set_selection_mode(GtkSheet *sheet, gint mode)
{
  g_return_if_fail (sheet != NULL);
  g_return_if_fail (GTK_IS_SHEET (sheet));

  if(GTK_WIDGET_REALIZED(sheet))
   gtk_sheet_real_unselect_range(sheet, NULL);

  sheet->selection_mode = mode;
}
