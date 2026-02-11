position_menu (GtkMenu *menu, gint *x, gint *y,
	       gboolean *push_in, gpointer user_data)
{
    GtkWidget *widget = GTK_WIDGET (user_data);
    GdkScreen *screen;
    gint twidth, theight, tx, ty;
    GtkAllocation allocation;
    GtkRequisition requisition;
    GtkTextDirection direction;
    GdkRectangle monitor;
    gint monitor_num;

    g_return_if_fail (menu != NULL);
    g_return_if_fail (x != NULL);
    g_return_if_fail (y != NULL);

    if (push_in) *push_in = FALSE;

    direction = gtk_widget_get_direction (widget);

    gtk_widget_get_requisition (GTK_WIDGET (menu), &requisition);
    twidth = requisition.width;
    theight = requisition.height;

    screen = gtk_widget_get_screen (GTK_WIDGET (menu));
    monitor_num = gdk_screen_get_monitor_at_window (screen, gtk_widget_get_window (widget));
    if (monitor_num < 0) monitor_num = 0;
    gdk_screen_get_monitor_geometry (screen, monitor_num, &monitor);

    if (!gdk_window_get_origin (gtk_widget_get_window (widget), &tx, &ty)) {
	g_warning ("Menu not on screen");
	return;
    }

    gtk_widget_get_allocation (widget, &allocation);
    tx += allocation.x;
    ty += allocation.y;

    if (direction == GTK_TEXT_DIR_RTL)
	tx += allocation.width - twidth;

    if ((ty + allocation.height + theight) <= monitor.y + monitor.height)
	ty += allocation.height;
    else if ((ty - theight) >= monitor.y)
	ty -= theight;
    else if (monitor.y + monitor.height - (ty + allocation.height) > ty)
	ty += allocation.height;
    else
	ty -= theight;

    *x = CLAMP (tx, monitor.x, MAX (monitor.x, monitor.x + monitor.width - twidth));
    *y = ty;
    gtk_menu_set_monitor (menu, monitor_num);
}
