graphics_cls(void) {
    int i;
    unsigned char *mem, *s1, *s2, *s4, *s8;

    graphics_cursor(0);
    graphics_gotoxy(view_x0, view_y0);

    mem = (unsigned char*)VIDEOMEM;
    s1 = (unsigned char*)VSHADOW1;
    s2 = (unsigned char*)VSHADOW2;
    s4 = (unsigned char*)VSHADOW4;
    s8 = (unsigned char*)VSHADOW8;

    for (i = 0; i < 80 * 30; i++)
        text[i] = ' ';
    graphics_cursor(1);

    BitMask(0xff);


    MapMask(1);
    grub_memcpy(mem, s1, 38400);


    MapMask(2);
    grub_memcpy(mem, s2, 38400);


    MapMask(4);
    grub_memcpy(mem, s4, 38400);


    MapMask(8);
    grub_memcpy(mem, s8, 38400);

    MapMask(15);

    if (no_cursor) {
        no_cursor = 0;
        set_int1c_handler();
    }
}
