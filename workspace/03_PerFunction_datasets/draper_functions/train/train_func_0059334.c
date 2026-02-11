position_cursor(bool toCenter, bool evenIfVisible) {


    const LineVector& cursorLine = get_last_drawed_cursor_position();
    sec_assert(cursorLine.valid());

    AWT_canvas *ntw    = db->canvas();
    AW_device  *device = ntw->aww->get_device(AW_MIDDLE_AREA);

    Rectangle cursor(device->transform(cursorLine));
    Rectangle screen = device->get_area_size();

    if (evenIfVisible || !screen.contains(cursor)) {
        if (!toCenter) {
            if (perform_autoscroll()) {
                cursor = Rectangle(device->transform(cursorLine));
                if (!screen.contains(cursor)) {
                    toCenter = true;
                }
            }
            else {
                toCenter = true;
            }
        }

        if (toCenter) {
            Vector scroll(cursor.centroid(), screen.centroid());

#if defined(DEBUG) && 1
            printf("Auto-scroll: scroll = (%f, %f) [Center cursor]\n", scroll.x(), scroll.y());
#endif
            ntw->scroll(NULL, -scroll, false);
            ntw->refresh();
        }
    }
}
