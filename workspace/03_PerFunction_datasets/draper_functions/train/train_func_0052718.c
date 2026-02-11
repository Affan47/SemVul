set_text_size(void)
{
    double x, y;

    x = (D_get_d_east() - D_get_d_west()) * hsize / 100.0;
    y = (D_get_d_north() - D_get_d_south()) * vsize / 100.0;
    if (x < 0)
	x = -x;
    if (y < 0)
	y = -y;

    R_text_size(abs((int)x), abs((int)y));
    return (0);
}
