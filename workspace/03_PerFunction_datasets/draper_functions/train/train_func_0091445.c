popup_position (GtkWidget *widget, GtkWindow *popup)
{
   GtkAllocation allocation;
   GtkRequisition requisition;
   gint x, y, width, height;

   gtk_widget_size_request (GTK_WIDGET (popup), &requisition);
   gdk_window_get_origin (gtk_widget_get_window (widget), &x, &y);

   gtk_widget_get_allocation (widget, &allocation);
   x += allocation.x;
   y += allocation.y;
   width  = allocation.width;
   height = allocation.height;

   x += width - requisition.width;
   y += height;

   if (x < 0)
      x = 0;
   if (y < 0)
      y = 0;

   gtk_window_move (popup, x, y);
}
