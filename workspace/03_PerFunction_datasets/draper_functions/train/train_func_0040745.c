hypotw(int re, int im)
{
    int abs_re = abs(re);
    int abs_im = abs(im);

    if (abs_re > 255)
    {
	abs_re = 255;
	fprintf(stderr, "TRUNC RE !!\n");
	fflush(stderr);
    }
    if (abs_im > 255)
    {
	abs_im = 255;
	fprintf(stderr, "TRUNC IM !!\n");
	fflush(stderr);
    }
    return hypot_tab[abs_re][abs_im];
}
