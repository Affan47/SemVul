freehand_button_release(gpaint_tool *tool, int x, int y)
{
    gpaint_closed_freehand *pen = GPAINT_CFH(tool);
    gdk_draw_line(tool->drawing->backing_pixmap, tool->drawing->gc,
                  x, y, pen->anchor.x, pen->anchor.y);
    gdk_draw_line(tool->drawing->window, tool->drawing->gc,
                  x, y, pen->anchor.x, pen->anchor.y);
    drawing_modified(tool->drawing);
    point_array_append(pen->points, pen->anchor.x, pen->anchor.y);

    if (pen->fill)
    {
       freehand_fill_area(tool->drawing, pen->points);
    }

    point_array_remove_all(pen->points);
    clear_point(&pen->anchor);
    clear_point(&pen->last);
}
