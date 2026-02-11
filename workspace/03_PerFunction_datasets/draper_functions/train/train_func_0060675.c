input_pad_gtk_button_press_real (GtkWidget      *widget,
                                 GdkEventButton *event)
{
    if (INPUT_PAD_IS_GTK_BUTTON (widget)) {
        start_timer (INPUT_PAD_GTK_BUTTON (widget));
    }
    return GTK_WIDGET_CLASS (input_pad_gtk_button_parent_class)->button_press_event (widget, event);
}
