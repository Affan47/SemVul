uc_blit_one_plane(void* drv, void* dev, DFBRectangle* rect, int dx, int dy)
{
    UC_ACCEL_BEGIN()


    int cmd = VIA_GEC_BLT | VIA_ROP_S | VIA_GEC_CLIP_ENABLE;

    int sx = rect->x;
    int sy = rect->y;
    int w = rect->w;
    int h = rect->h;

    if (!w || !h) return true;

    (void) ucdev;

    if (sx < dx) {
        cmd |= VIA_GEC_DECX;
        sx += w - 1;
        dx += w - 1;
    }

    if (sy < dy) {
        cmd |= VIA_GEC_DECY;
        sy += h - 1;
        dy += h - 1;
    }

    UC_FIFO_PREPARE(fifo, 10);

    UC_FIFO_ADD_HDR(fifo, HC_ParaType_NotTex << 16);

    UC_FIFO_ADD_2D(fifo, VIA_REG_SRCPOS, (RS16(sy) << 16) | RS16(sx));
    UC_FIFO_ADD_2D(fifo, VIA_REG_DSTPOS, (RS16(dy) << 16) | RS16(dx));
    UC_FIFO_ADD_2D(fifo, VIA_REG_DIMENSION, (RS16(h - 1) << 16) | RS16(w - 1));
    UC_FIFO_ADD_2D(fifo, VIA_REG_GECMD, cmd);

    UC_ACCEL_END();
    return true;
}
