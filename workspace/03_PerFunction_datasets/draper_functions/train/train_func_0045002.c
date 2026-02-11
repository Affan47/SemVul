gdl_dock_tablabel_realize (GtkWidget *widget)
{
    GdlDockTablabel *tablabel;
    GdkWindowAttr attributes;
    int attributes_mask;

    tablabel = GDL_DOCK_TABLABEL (widget);

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    attributes.width = widget->allocation.width;
    attributes.height = widget->allocation.height;
    attributes.wclass = GDK_INPUT_ONLY;
    attributes.event_mask = gtk_widget_get_events (widget);
    attributes.event_mask |= (GDK_EXPOSURE_MASK |
                              GDK_BUTTON_PRESS_MASK |
                              GDK_BUTTON_RELEASE_MASK |
                              GDK_ENTER_NOTIFY_MASK |
                              GDK_POINTER_MOTION_MASK |
                              GDK_LEAVE_NOTIFY_MASK);
    attributes_mask = GDK_WA_X | GDK_WA_Y;

    widget->window = gtk_widget_get_parent_window (widget);
    g_object_ref (widget->window);

    tablabel->event_window =
        gdk_window_new (gtk_widget_get_parent_window (widget),
                        &attributes, attributes_mask);
    gdk_window_set_user_data (tablabel->event_window, widget);

    widget->style = gtk_style_attach (widget->style, widget->window);

    GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);
}
