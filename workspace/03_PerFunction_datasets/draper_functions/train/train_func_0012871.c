drv_generic_graphic_icon_draw(WIDGET * W)
{
    WIDGET_ICON *Icon = W->data;
    RGBA fg, bg;
    unsigned char *bitmap = Icon->bitmap + YRES * Icon->curmap;
    int layer, row, col;
    int x, y;
    int visible;

    layer = W->layer;
    row = YRES * W->row;
    col = XRES * W->col;

    fg = W->fg_valid ? W->fg_color : FG_COL;
    bg = W->bg_valid ? W->bg_color : BG_COL;


    if (layer < 0 || layer >= LAYERS) {
	error("%s: layer %d out of bounds (0..%d)", Driver, layer, LAYERS - 1);
	return -1;
    }


    drv_generic_graphic_resizeFB(row + YRES, col + XRES);


    visible = P2N(&Icon->visible) > 0;


    for (y = 0; y < YRES; y++) {
	int mask = 1 << XRES;
	for (x = 0; x < XRES; x++) {
	    int i = (row + y) * LCOLS + col + x;
	    mask >>= 1;
	    if (visible) {
		if (bitmap[y] & mask)
		    drv_generic_graphic_FB[layer][i] = fg;
		else
		    drv_generic_graphic_FB[layer][i] = bg;
	    } else {
		drv_generic_graphic_FB[layer][i] = BG_COL;
	    }
	}
    }


    drv_generic_graphic_blit(row, col, YRES, XRES);

    return 0;

}
