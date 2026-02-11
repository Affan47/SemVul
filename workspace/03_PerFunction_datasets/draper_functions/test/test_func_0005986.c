expose_event(GtkWidget      *widget,
             GdkEventExpose *event,
             gpointer        data)
{
    GwyColorButton *color_button = GWY_COLOR_BUTTON(data);

    gint width = color_button->drawing_area->allocation.width;
    gint height = color_button->drawing_area->allocation.height;

    if (color_button->pixbuf == NULL
        || width != gdk_pixbuf_get_width(color_button->pixbuf)
        || height != gdk_pixbuf_get_height(color_button->pixbuf))
        render(color_button);

    gdk_draw_pixbuf(widget->window,
                    color_button->gc,
                    color_button->pixbuf,
                    event->area.x,
                    event->area.y,
                    event->area.x,
                    event->area.y,
                    event->area.width,
                    event->area.height,
                    GDK_RGB_DITHER_MAX,
                    event->area.x,
                    event->area.y);
    return FALSE;
}
