size_allocate_column_title_buttons (GtkSheet * sheet)
{
  gint i;
  gint x,width;

  if (!sheet->column_titles_visible) return;
  if (!GTK_WIDGET_REALIZED (sheet))
    return;

  width = sheet->sheet_window_width;
  x = 0;

  if(sheet->row_titles_visible)
    {
      width -= sheet->row_title_area.width;
      x = sheet->row_title_area.width;
    }

  if(sheet->column_title_area.width != width || sheet->column_title_area.x != x)
  {
     sheet->column_title_area.width = width;
     sheet->column_title_area.x = x;
     gdk_window_move_resize (sheet->column_title_window,
  		  	     sheet->column_title_area.x,
			     sheet->column_title_area.y,
			     sheet->column_title_area.width,
			     sheet->column_title_area.height);
  }


  if(MAX_VISIBLE_COLUMN(sheet) == sheet->maxcol)
     gdk_window_clear_area (sheet->column_title_window,
	   		    0,0,
			    sheet->column_title_area.width,
                            sheet->column_title_area.height);

  if(!GTK_WIDGET_DRAWABLE(sheet)) return;

  for (i = MIN_VISIBLE_COLUMN(sheet); i <= MAX_VISIBLE_COLUMN(sheet); i++)
      gtk_sheet_button_draw(sheet,-1,i);
}
