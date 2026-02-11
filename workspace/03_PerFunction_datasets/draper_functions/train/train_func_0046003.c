make_gray_scale(struct Colors *gray)
{
    int i;

    G_init_colors(gray);

    for (i = 0; i < 256; i++)
	G_set_color((CELL) i, i, i, i, gray);

    return 0;
}
