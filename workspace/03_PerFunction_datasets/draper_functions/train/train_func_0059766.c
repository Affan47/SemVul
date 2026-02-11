new_column_width (GtkSheet * sheet,
		  gint column,
		  gint * x)
{
  gint cx, width;
  GtkRequisition requisition;

  cx = *x;

  requisition.width = sheet->column[column].requisition;


  if (cx < COLUMN_LEFT_XPIXEL (sheet, column) + requisition.width)
    {
      *x = cx = COLUMN_LEFT_XPIXEL (sheet, column) + requisition.width;
    }


  width = cx - COLUMN_LEFT_XPIXEL (sheet, column);
  if (width < requisition.width)
    width = requisition.width;

  sheet->column[column].width = width;
  gtk_sheet_recalc_left_xpixels(sheet, column+1);
  sheet->view.coli=COLUMN_FROM_XPIXEL(sheet, sheet->sheet_window_width);
  size_allocate_column_title_buttons (sheet);

  return width;
}
