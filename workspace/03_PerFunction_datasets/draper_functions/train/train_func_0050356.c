x11_set_color(int r, int g, int b, int init)
{
    if (init)
	xfree_colors(d);
    return (xalloc_color(d, r * 256, g * 256, b * 256, init));
}
