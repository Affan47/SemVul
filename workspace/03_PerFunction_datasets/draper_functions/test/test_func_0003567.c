D_show_window(int color)
{
    int t, b, l, r;
    int stat;

    if ((stat = D_get_screen_window(&t, &b, &l, &r)))
	return (stat);

    R_set_window(t - 1, b + 1, l - 1, r + 1);

    R_standard_color(color);
    R_move_abs(l - 1, b);
    R_cont_abs(l - 1, t - 1);
    R_cont_abs(r, t - 1);
    R_cont_abs(r, b);
    R_cont_abs(l - 1, b);
    R_flush();

    R_set_window(t, b, l, r);

    return (0);
}
