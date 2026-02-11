monitor_horizontal_scroll_cb(AW_window *aww) {
    if (!device) return;

    long old_horiz_page_start = horiz_page_start;

    horiz_last_view_start = aww->slider_pos_horizontal;
    horiz_page_start      = aww->slider_pos_horizontal/cell_width;

    long diff = horiz_page_start-old_horiz_page_start;

    if (diff) {
        bool clear = false;

        if (diff>0 && diff<horiz_page_size) {
            int keep_cells = horiz_page_size-diff;

            device->move_region(off_dx+diff*cell_width, 0, keep_cells*cell_width, screen_height, off_dx, 0);
            device->clear_part(off_dx+keep_cells*cell_width, 0, diff*cell_width, screen_height, -1);
            device->push_clip_scale();
            device->set_left_clip_border((int)(keep_cells*cell_width));
        }
        else if (diff>-horiz_page_size && diff<0) {
            int keep_cells = horiz_page_size+diff;

            device->move_region(off_dx, 0, keep_cells*cell_width, screen_height, off_dx+cell_width*-diff, 0);
            device->clear_part(off_dx, 0, cell_width*-diff, screen_height, -1);
            device->push_clip_scale();
            device->set_right_clip_border((int)(off_dx+cell_width*-diff));
        }
        else {
            device->push_clip_scale();
            clear = true;
        }

        display(clear);
        device->pop_clip_scale();
    }
}
