gtk_sheet_remove (GtkContainer *container, GtkWidget *widget)
{
  GtkSheet *sheet;
  GList *children;
  GtkSheetChild *child = 0;

  g_return_if_fail(container != NULL);
  g_return_if_fail(GTK_IS_SHEET(container));

  sheet = GTK_SHEET(container);

  children = sheet->children;

  while(children)
   {
     child = (GtkSheetChild *)children->data;

     if(child->widget == widget) break;

     children = g_list_next(children);
   }

  if (children)
   {
     if(child->row == -1)
        sheet->row[child->col].button.child = NULL;

     if(child->col == -1)
        sheet->column[child->row].button.child = NULL;

     gtk_widget_unparent (widget);
     child->widget = NULL;

     sheet->children = g_list_remove_link (sheet->children, children);
     g_list_free_1 (children);
     g_free(child);
   }

}
