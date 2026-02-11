read_image_header(struct gif_info *g)
{
    unsigned int	misc_bits;

    if (g->src_len < 9)
	return -1;

    (void)NEXT_BYTE(g); (void)NEXT_BYTE(g);
    (void)NEXT_BYTE(g); (void)NEXT_BYTE(g);
    g->width   = NEXT_BYTE(g);
    g->width  += NEXT_BYTE(g) << 8;
    g->height  = NEXT_BYTE(g);
    g->height += NEXT_BYTE(g) << 8;
    misc_bits  = NEXT_BYTE(g);

    g->interlaced = (misc_bits & 0x40) ? True : False;

    if (read_cmap(g, misc_bits) < 0)
	return -1;

    return 0;
}
