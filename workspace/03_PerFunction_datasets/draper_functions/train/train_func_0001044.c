_render_rle(GRAPHICS_CONTROLLER *gc,
                        int64_t pts,
                        BD_PG_RLE_ELEM *img,
                        uint16_t x, uint16_t y,
                        uint16_t width, uint16_t height,
                        BD_PG_PALETTE_ENTRY *palette)
{
    if (gc->overlay_proc) {
        BD_OVERLAY ov = {0};
        ov.cmd     = BD_OVERLAY_DRAW;
        ov.pts     = pts;
        ov.plane   = BD_OVERLAY_PG;
        ov.x       = x;
        ov.y       = y;
        ov.w       = width;
        ov.h       = height;
        ov.palette = palette;
        ov.img     = img;

        gc->overlay_proc(gc->overlay_proc_handle, &ov);
    }
}
