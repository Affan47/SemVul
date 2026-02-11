win_graphics_create(window_t *win)
{
    window_graphics_t *res;

    if (!gli_conf_graphics)
        return NULL;

    res = malloc(sizeof(window_graphics_t));
    if (!res)
        return NULL;

    res->owner = win;
    res->bgnd[0] = win->bgcolor[0];
    res->bgnd[1] = win->bgcolor[1];
    res->bgnd[2] = win->bgcolor[2];

    res->w = 0;
    res->h = 0;
    res->rgb = NULL;

    res->dirty = 0;

    return res;
}
