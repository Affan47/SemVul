gli_calc_padding(window_t *win, int *x, int *y)
{
    window_pair_t *wp;
    if (!win)
        return;
    if (win->type == wintype_Pair)
    {
        wp = win->data;
        if (wp->vertical)
            *x += gli_wpaddingx;
        else
            *y += gli_wpaddingy;
        gli_calc_padding(wp->child1, x, y);
        gli_calc_padding(wp->child2, x, y);
    }
}
