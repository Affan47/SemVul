gnc_header_request_redraw (GncHeader *header)
{
    GnomeCanvas *canvas = GNOME_CANVAS_ITEM(header)->canvas;

    if (header->style == NULL)
        return;

    gnome_canvas_request_redraw (canvas, 0, 0,
                                 header->width + 1,
                                 header->height + 1);
}
