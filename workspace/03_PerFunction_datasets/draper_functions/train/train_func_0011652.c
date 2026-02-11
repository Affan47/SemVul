gui_widget_update_focus(
    GuiWidget *widget, int mx, int my, GuiWidget **focused_widget )
{
    GuiWidget *child;
    if ( !widget->active )
        return;
    if ( !STK_IN_RECT( widget->screen_region, mx, my ) )
        return;
    widget->focused = 1;
    *focused_widget = widget;

    list_reset( widget->widgets );
    while ( ( child = list_next( widget->widgets ) ) )
        gui_widget_update_focus( child, mx, my, focused_widget );
}
