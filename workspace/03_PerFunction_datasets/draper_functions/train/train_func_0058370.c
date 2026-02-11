label_button_expose_cb (GtkWidget      *widget,
                        GdkEventExpose *event,
                        SyncConfigWidget *self)
{
    GtkExpanderStyle style;
    gint indicator_x, indicator_y;

    indicator_x = widget->style->xthickness + INDICATOR_SIZE / 2;
    indicator_y = widget->style->ythickness +
                  widget->allocation.height / 2;

    if (self->expanded) {
        style = GTK_EXPANDER_EXPANDED;
    } else {
        style = GTK_EXPANDER_COLLAPSED;
    }

    gtk_paint_expander (widget->style,
                        widget->window,
                        widget->state,
                        NULL,
                        GTK_WIDGET (self),
                        NULL,
                        indicator_x,
                        indicator_y,
                        style);

    return FALSE;
}
