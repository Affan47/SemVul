gui_widget_move( GuiWidget *widget, int rel_x, int rel_y )
{
    if ( !widget->visible )
        gui_widget_move_intern( widget, rel_x, rel_y );
    else {
        gui_widget_hide( widget );
        gui_widget_move_intern( widget, rel_x, rel_y );
        gui_widget_show( widget );
    }
}
