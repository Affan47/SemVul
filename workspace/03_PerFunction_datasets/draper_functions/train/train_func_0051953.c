gtk_sheet_draw_active_cell(GtkSheet *sheet)
{
    gint row, col;

    if(!GTK_WIDGET_DRAWABLE(GTK_WIDGET(sheet))) return;
    if(!GTK_WIDGET_REALIZED(GTK_WIDGET(sheet))) return;

    row = sheet->active_cell.row;
    col = sheet->active_cell.col;

    if(row<0 || col<0) return;

    if(!gtk_sheet_cell_isvisible(sheet, row, col)) return;

    row_button_set(sheet, row);
    column_button_set(sheet, col);

    gtk_sheet_draw_backing_pixmap(sheet, sheet->range);
    gtk_sheet_draw_border(sheet, sheet->range);

}
