drawGraphPng(char *filename, struct _graph_data *graph, int width, int height)
{
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);

    cairo_rectangle(cr, 0,0,width,height);
    cairo_stroke_preserve(cr);
    if(transparent)
    {
        if(inverted)
            cairo_set_source_rgba(cr, 0,0,0,0);
        else
            cairo_set_source_rgba(cr, 255,255,255,0);
    }
    else
    {
        if(inverted)
            cairo_set_source_rgba(cr, 0,0,0,1);
        else
            cairo_set_source_rgba(cr, 255,255,255,1);
    }
    cairo_fill(cr);

    drawGraph(cr, graph, width, height);

    cairo_surface_write_to_png(surface, filename);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
