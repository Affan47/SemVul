_pre_border_assign_hook(void *data __UNUSED__,
                        E_Border *bd)
{
    if (tiling_g.config->show_titles)
        return;

    if (!bd) {
        return;
    }

    check_tinfo(bd->desk);
    if (!_G.tinfo->conf || !_G.tinfo->conf->nb_stacks) {
        return;
    }

    if (is_floating_window(bd)) {
        return;
    }

    if (!is_tilable(bd)) {
        return;
    }

    if (bd->fullscreen) {
         return;
    }


    _get_or_create_border_extra(bd);

    if ((bd->bordername && strcmp(bd->bordername, "pixel"))
    ||  !bd->bordername)
    {
        change_window_border(bd, "pixel");
    }
}
