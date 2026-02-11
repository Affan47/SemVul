gli_set_reversevideo(stream_t *str, glui32 reverse)
{
    if (!str || !str->writable)
        return;

    if (!gli_conf_stylehint)
        return;

    switch (str->type)
    {
        case strtype_Window:
            str->win->attr.reverse = (reverse != 0);
            if (str->win->echostr)
                gli_set_reversevideo(str->win->echostr, reverse);
            break;
    }
    gli_force_redraw = 1;
}
