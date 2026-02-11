saveGeometry(int new_x, int new_y,
                               unsigned int new_w, unsigned int new_h,
                               bool force) {
    if ((fullscreen || maximized == MAX_FULL) && !force)
        return;

    if (!(maximized & MAX_HORZ) || force) {
        x = new_x;
        width = new_w;
    }
    if (!(maximized & MAX_VERT) || force) {
        y = new_y;
        if (!shaded || force)
            height = new_h;
    }
}
