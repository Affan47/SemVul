gtk_sheet_extend_selection(GtkSheet *sheet, gint row, gint column)
{
   GtkSheetRange range;
   gint state;
   gint r,c;

   if(row == sheet->selection_cell.row && column == sheet->selection_cell.col)
        return;

   if(sheet->selection_mode == GTK_SELECTION_SINGLE) return;

   gtk_sheet_move_query(sheet, row, column);
   gtk_widget_grab_focus(GTK_WIDGET(sheet));

   if(GTK_SHEET_IN_DRAG(sheet)) return;

   state=sheet->state;

   switch(sheet->state){
    case GTK_SHEET_ROW_SELECTED:
	 column = sheet->maxcol;
         break;
    case GTK_SHEET_COLUMN_SELECTED:
	 row = sheet->maxrow;
         break;
    case GTK_SHEET_NORMAL:
	 sheet->state=GTK_SHEET_RANGE_SELECTED;
         r=sheet->active_cell.row;
         c=sheet->active_cell.col;
         sheet->range.col0=c;
         sheet->range.row0=r;
         sheet->range.coli=c;
         sheet->range.rowi=r;
         gdk_draw_pixmap(sheet->sheet_window,
                   GTK_WIDGET(sheet)->style->fg_gc[GTK_STATE_NORMAL],
                   sheet->pixmap,
                   COLUMN_LEFT_XPIXEL(sheet,c)-1,
                   ROW_TOP_YPIXEL(sheet,r)-1,
                   COLUMN_LEFT_XPIXEL(sheet,c)-1,
                   ROW_TOP_YPIXEL(sheet,r)-1,
                   sheet->column[c].width+4,
                   sheet->row[r].height+4);
         gtk_sheet_range_draw_selection(sheet, sheet->range);
    case GTK_SHEET_RANGE_SELECTED:
         sheet->state=GTK_SHEET_RANGE_SELECTED;
   }

   sheet->selection_cell.row = row;
   sheet->selection_cell.col = column;

   range.col0=MIN(column,sheet->active_cell.col);
   range.coli=MAX(column,sheet->active_cell.col);
   range.row0=MIN(row,sheet->active_cell.row);
   range.rowi=MAX(row,sheet->active_cell.row);

   if(range.row0 != sheet->range.row0 || range.rowi != sheet->range.rowi ||
      range.col0 != sheet->range.col0 || range.coli != sheet->range.coli ||
      state==GTK_SHEET_NORMAL)
               gtk_sheet_real_select_range(sheet, &range);

}
