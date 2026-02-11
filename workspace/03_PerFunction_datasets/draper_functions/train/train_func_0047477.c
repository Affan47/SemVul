draw_line (GtkWidget      *widget,
    GdkEventButton *event,
    gamine_t *cb)
{
    cairo_t *drawingline;

    if (! xold)
    {
        xold=event->x+1;
        yold=event->y;
    } else {
        float red = ((rand() % 128) + 127) /255.0;
        float green = ((rand() % 128) + 127) /255.0;
        float blue = ((rand() % 128) + 127) /255.0;
        drawingline = get_cairo_context(cb);
        cairo_new_path (drawingline);
        cairo_set_source_rgba (drawingline, red, green, blue, 0.5);
        cairo_set_line_width (drawingline, linewidth);

        cairo_move_to (drawingline, xold, yold);

        cairo_line_to (drawingline, event->x+1, event->y);

        cairo_stroke (drawingline);
        xold=event->x+1;
        yold=event->y;
    }
}
