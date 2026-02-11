__vesacon_erase(int x0, int y0, int x1, int y1, attr_t attr)
{
    int y;
    struct vesa_char *ptr = &__vesacon_text_display
	[(y0 + 1) * (__vesacon_text_cols + 2) + (x0 + 1)];
    struct vesa_char fill = {
	.ch = ' ',
	.attr = attr,
    };
    int ncols = x1 - x0 + 1;

    for (y = y0; y <= y1; y++) {
	vesacon_fill(ptr, fill, ncols);
	ptr += __vesacon_text_cols + 2;
    }

    vesacon_touch(y0, x0, y1 - y0 + 1, ncols);
}
