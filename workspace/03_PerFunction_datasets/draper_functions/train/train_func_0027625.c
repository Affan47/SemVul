menu_pos(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, GtkWidget *widget)
{
    int ox, oy, w, h;

    ENTER;
    if (widget) {
        gdk_window_get_origin(widget->window, &ox, &oy);
        ox += widget->allocation.x;
        oy += widget->allocation.y;
    } else {
        gdk_display_get_pointer(gdk_display_get_default(), NULL, &ox, &oy, NULL);
        ox -= 20;
        if (ox < 0)
            ox = 0;
        oy -= 10;
        if (oy < 0)
            oy = 0;
    }
    w = GTK_WIDGET(menu)->requisition.width;
    h = GTK_WIDGET(menu)->requisition.height;
    if (the_panel->orientation == GTK_ORIENTATION_HORIZONTAL) {

        *x = ox;
        if (*x + w > gdk_screen_width())
            *x = gdk_screen_width() - w;

        if (the_panel->edge == EDGE_TOP)
            *y = the_panel->ah;
        else
            *y = gdk_screen_height() - the_panel->ah - h;
    } else {

        if (the_panel->edge == EDGE_LEFT)
            *x = the_panel->aw;
        else
            *x = gdk_screen_width() - the_panel->aw - w;

        *y = oy;
        if (*y + h > gdk_screen_height())
            *y = gdk_screen_height() - h;
    }
    DBG("w-h %d %d\n", w, h);
    *push_in = TRUE;
    RET();
}
