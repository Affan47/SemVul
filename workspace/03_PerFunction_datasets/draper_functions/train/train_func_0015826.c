gtk_sheet_get_columns_count(GtkSheet *sheet)
{
  g_return_val_if_fail (sheet != NULL, 0);
  g_return_val_if_fail (GTK_IS_SHEET (sheet), 0);

  return sheet->maxcol + 1;
}
