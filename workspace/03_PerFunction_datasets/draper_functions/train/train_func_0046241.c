gtk_sheet_insert_columns(GtkSheet *sheet, guint col, guint ncols)
{
 GList *children;
 GtkSheetChild *child;

 g_return_if_fail (sheet != NULL);
 g_return_if_fail (GTK_IS_SHEET (sheet));

 if(GTK_WIDGET_REALIZED(sheet))
   gtk_sheet_real_unselect_range(sheet, NULL);

 InsertColumn(sheet, col, ncols);

 children = sheet->children;
 while(children)
   {
     child = (GtkSheetChild *)children->data;

     if(child->attached_to_cell)
        if(child->col >= col) child->col += ncols;

     children = g_list_next(children);
   }

 if(!GTK_WIDGET_REALIZED(sheet)) return;

 if(sheet->state==GTK_SHEET_ROW_SELECTED) sheet->range.coli+=ncols;
 adjust_scrollbars(sheet);

 sheet->old_hadjustment = -1.;
 if(!GTK_SHEET_IS_FROZEN(sheet) && sheet->hadjustment)
      gtk_signal_emit_by_name (GTK_OBJECT (sheet->hadjustment),
			       "value_changed");

}
