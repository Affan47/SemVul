display_raster(gx_device_display *dev)
{
    int align = 0;
    int bytewidth = ((dev->width * dev->color_info.depth) + 7) /8;
    switch (dev->nFormat & DISPLAY_ROW_ALIGN_MASK) {
        case DISPLAY_ROW_ALIGN_4:
            align = 4;
            break;
        case DISPLAY_ROW_ALIGN_8:
            align = 8;
            break;
        case DISPLAY_ROW_ALIGN_16:
            align = 16;
            break;
        case DISPLAY_ROW_ALIGN_32:
            align = 32;
            break;
        case DISPLAY_ROW_ALIGN_64:
            align = 64;
            break;
    }
    if (align < ARCH_ALIGN_PTR_MOD)
        align = ARCH_ALIGN_PTR_MOD;
    align -= 1;
    bytewidth = (bytewidth + align) & (~align);
    return bytewidth;
}
