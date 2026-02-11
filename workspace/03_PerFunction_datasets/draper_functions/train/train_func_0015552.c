_bdf_grid_ink_bounds(bdf_glyph_grid_t *grid, short *x, short *y,
                     short *width, short *height)
#else
_bdf_grid_ink_bounds(grid, x, y, width, height)
bdf_glyph_grid_t *grid;
short *x, *y, *width, *height;
#endif
{
    short bx, by, bwd, bht, minx, maxx, miny, maxy, dx, dy;
    unsigned short bpr, ink, sel, col;
    unsigned char *bmap, *masks;

    masks = 0;
    switch (grid->bpp) {
      case 1: masks = onebpp; break;
      case 2: masks = twobpp; break;
      case 4: masks = fourbpp; break;
    }

    if (grid->sel.width != 0 && grid->sel.height != 0) {
        sel = 1;
        bx = by = 0;
        bwd = grid->sel.width;
        bht = grid->sel.height;
        bmap = grid->sel.bitmap;
    } else {
        sel = 0;
        bx = grid->glyph_x;
        by = grid->glyph_y;
        bwd = grid->glyph_bbx.width;
        bht = grid->glyph_bbx.height;
        bmap = grid->bitmap;
    }
    maxx = maxy = 0;
    minx = bx + bwd;
    miny = by + bht;

    bpr = ((bwd * grid->bpp) + 7) >> 3;
    ink = 0;

    bwd += bx;
    bht += by;
    for (dy = by; dy < bht; dy++) {
        for (col = bx * grid->bpp, dx = bx; dx < bwd; dx++, col += grid->bpp) {
            if (bmap[(dy * bpr) + (col >> 3)] & masks[(col & 7) / grid->bpp]) {
                ink = 1;
                minx = MIN(minx, dx);
                miny = MIN(miny, dy);
                maxx = MAX(maxx, dx);
                maxy = MAX(maxy, dy);
            }
        }
    }

    *x = minx + ((sel) ? grid->sel.x : 0);
    *y = miny + ((sel) ? grid->sel.y : 0);
    if (ink == 0)
      *width = *height = 0;
    else {
        *width = (maxx - minx) + 1;
        *height = (maxy - miny) + 1;
    }
    return ink;
}
