gnc_header_reconfigure (GncHeader *header)
{
    GnomeCanvas *canvas;
    GnucashSheet *sheet;
    SheetBlockStyle *old_style;
    int w, h;

    g_return_if_fail (header != NULL);
    g_return_if_fail (GNC_IS_HEADER (header));

    canvas = GNOME_CANVAS_ITEM(header)->canvas;
    sheet = GNUCASH_SHEET(header->sheet);
    old_style = header->style;

    header->style = gnucash_sheet_get_style_from_cursor
                    (sheet, header->cursor_name);

    if (header->style == NULL)
        return;

    sheet->width = header->style->dimensions->width;

    w = header->style->dimensions->width;
    h = header->style->dimensions->height;
    h *= header->num_phys_rows;
    h /= header->style->nrows;
    h += 2;

    if (header->height != h ||
            header->width != w  ||
            header->style != old_style)
    {
        header->height = h;
        header->width = w;

        gnome_canvas_set_scroll_region (GNOME_CANVAS(canvas),
                                        0, 0, w, h);

        gtk_widget_set_size_request (GTK_WIDGET(canvas), -1, h);

        gnc_header_request_redraw (header);
    }
}
