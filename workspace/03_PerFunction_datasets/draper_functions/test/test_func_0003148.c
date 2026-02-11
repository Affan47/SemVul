gwy_color_button_realize (GtkWidget *widget)
{
    GwyColorButton *color_button = GWY_COLOR_BUTTON(widget);

    GTK_WIDGET_CLASS(gwy_color_button_parent_class)->realize(widget);

    if (color_button->gc == NULL)
        color_button->gc = gdk_gc_new(widget->window);

    render(color_button);
}
