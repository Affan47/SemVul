graphics_putchar(int ch) {
    ch &= 0xff;

    graphics_cursor(0);

    if (ch == '\n') {
        if (fonty + 1 < view_y1)
            graphics_setxy(fontx, fonty + 1);
        else
            graphics_scroll();
        graphics_cursor(1);
        return;
    } else if (ch == '\r') {
        graphics_setxy(view_x0, fonty);
        graphics_cursor(1);
        return;
    }

    graphics_cursor(0);

    text[fonty * 80 + fontx] = ch;
    text[fonty * 80 + fontx] &= 0x00ff;
    if (graphics_current_color & 0xf0)
        text[fonty * 80 + fontx] |= 0x100;

    graphics_cursor(0);

    if ((fontx + 1) >= view_x1) {
        graphics_setxy(view_x0, fonty);
        if (fonty + 1 < view_y1)
            graphics_setxy(view_x0, fonty + 1);
        else
            graphics_scroll();
        graphics_cursor(1);
        do_more ();
        graphics_cursor(0);
    } else {
        graphics_setxy(fontx + 1, fonty);
    }

    graphics_cursor(1);
}
