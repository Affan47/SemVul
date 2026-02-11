gtk_sheet_columns_set_sensitivity(GtkSheet *sheet, gboolean sensitive)
{
  gint i;

  g_return_if_fail (sheet != NULL);
  g_return_if_fail (GTK_IS_SHEET (sheet));

  for(i=0; i<=sheet->maxcol; i++)
     gtk_sheet_column_set_sensitivity(sheet, i, sensitive);
}
