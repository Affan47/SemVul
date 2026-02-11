statusline (uae_u8 *dst)
{
    int y, yy, slx, sly;
    int dst_height, dst_width, pitch;

    dst_height = picasso96_state.Height;
    if (dst_height > picasso_vidinfo.height)
        dst_height = picasso_vidinfo.height;
    dst_width = picasso96_state.Width;
    if (dst_width > picasso_vidinfo.width)
        dst_width = picasso_vidinfo.width;
    pitch = picasso_vidinfo.rowbytes;
    statusline_getpos (&slx, &sly, picasso96_state.Width, dst_height);
    yy = 0;
    for (y = 0; y < TD_TOTAL_HEIGHT; y++) {
        uae_u8 *buf = dst + (y + sly) * pitch;
        draw_status_line_single (buf, picasso_vidinfo.pixbytes, y, dst_width, p96rc, p96gc, p96bc, NULL);
        yy++;
    }
}
