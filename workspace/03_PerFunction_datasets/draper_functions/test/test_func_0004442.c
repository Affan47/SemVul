uc_draw_line(void* drv, void* dev, DFBRegion* line)
{
    UC_ACCEL_BEGIN()


    int cmd;
    int dx, dy, tmp, error;

    error = 1;

    cmd = VIA_GEC_LINE | VIA_GEC_FIXCOLOR_PAT | ucdev->draw_rop2d
        | VIA_GEC_CLIP_ENABLE;

    dx = line->x2 - line->x1;
    if (dx < 0)
    {
        dx = -dx;
        cmd |= VIA_GEC_DECX;
        error = 0;
    }

    dy = line->y2 - line->y1;
    if (dy < 0)
    {
        dy = -dy;
        cmd |= VIA_GEC_DECY;
    }

    if (dy > dx)
    {
        tmp  = dy;
        dy = dx;
        dx = tmp;
        cmd |= VIA_GEC_Y_MAJOR;
    }

    UC_FIFO_PREPARE(fifo, 12);

    UC_FIFO_ADD_HDR(fifo, HC_ParaType_NotTex << 16);

    UC_FIFO_ADD_2D(fifo, VIA_REG_LINE_K1K2,
        ((((dy << 1) & 0x3fff) << 16)| (((dy - dx) << 1) & 0x3fff)));
    UC_FIFO_ADD_2D(fifo, VIA_REG_LINE_XY,
        ((RS16(line->y1) << 16) | RS16(line->x1)));
    UC_FIFO_ADD_2D(fifo, VIA_REG_DIMENSION, dx);
    UC_FIFO_ADD_2D(fifo, VIA_REG_LINE_ERROR,
        (((dy << 1) - dx - error) & 0x3fff));
    UC_FIFO_ADD_2D(fifo, VIA_REG_GECMD, cmd);

    UC_ACCEL_END();
    return true;
}
