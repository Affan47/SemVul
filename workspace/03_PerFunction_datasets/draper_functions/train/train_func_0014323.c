store(const AW_at *at) {
    to_position_exists = at->to_position_exists;
    if (to_position_exists) {
        to_offset_x = at->to_position_x - at->x_for_next_button;
        to_offset_y = at->to_position_y - at->y_for_next_button;
    }
    attach_x   = at->attach_x;
    attach_y   = at->attach_y;
    attach_lx  = at->attach_lx;
    attach_ly  = at->attach_ly;
    attach_any = at->attach_any;
}
