popup_button_draw (GtkWidget      *widget,
                   cairo_t        *cr,
                   UmPhotoDialog  *um)
{
        if (gtk_widget_get_state (gtk_bin_get_child (GTK_BIN (widget))) != GTK_STATE_PRELIGHT &&
            !gtk_widget_is_focus (widget)) {
                return;
        }

        down_arrow (gtk_widget_get_style_context (widget),
                    cr,
                    gtk_widget_get_allocated_width (widget) - 12,
                    gtk_widget_get_allocated_height (widget) - 12,
                    12, 12);
}
