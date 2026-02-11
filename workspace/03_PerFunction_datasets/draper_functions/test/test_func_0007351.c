vnc_connection_read_pixel_format(VncConnection *conn, VncPixelFormat *fmt)
{
    guint8 pad[3];

    fmt->bits_per_pixel  = vnc_connection_read_u8(conn);
    fmt->depth           = vnc_connection_read_u8(conn);
    fmt->byte_order      = vnc_connection_read_u8(conn) ? G_BIG_ENDIAN : G_LITTLE_ENDIAN;
    fmt->true_color_flag = vnc_connection_read_u8(conn);

    fmt->red_max         = vnc_connection_read_u16(conn);
    fmt->green_max       = vnc_connection_read_u16(conn);
    fmt->blue_max        = vnc_connection_read_u16(conn);

    fmt->red_shift       = vnc_connection_read_u8(conn);
    fmt->green_shift     = vnc_connection_read_u8(conn);
    fmt->blue_shift      = vnc_connection_read_u8(conn);

    vnc_connection_read(conn, pad, 3);

    VNC_DEBUG("Pixel format BPP: %d,  Depth: %d, Byte order: %d, True color: %d\n"
              "             Mask  red: %3d, green: %3d, blue: %3d\n"
              "             Shift red: %3d, green: %3d, blue: %3d",
              fmt->bits_per_pixel, fmt->depth, fmt->byte_order, fmt->true_color_flag,
              fmt->red_max, fmt->green_max, fmt->blue_max,
              fmt->red_shift, fmt->green_shift, fmt->blue_shift);
}
