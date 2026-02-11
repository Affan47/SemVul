gtk_sheet_attach_default        (GtkSheet *sheet,
                                 GtkWidget *widget,
                                 gint row, gint col)
{
  if(row < 0 || col < 0){
    gtk_sheet_button_attach(sheet, widget, row, col);
    return;
  }

  gtk_sheet_attach(sheet, widget, row, col, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 0, 0);
}
