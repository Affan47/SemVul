glk_window_set_arrangement(window_t *win, glui32 method, glui32 size, winid_t key)
{
    window_pair_t *dwin;
    glui32 newdir;
    int newvertical, newbackward;

    gli_force_redraw = 1;

    if (!win)
    {
        gli_strict_warning("window_set_arrangement: invalid ref");
        return;
    }

    if (win->type != wintype_Pair)
    {
        gli_strict_warning("window_set_arrangement: not a Pair window");
        return;
    }

    if (key)
    {
        window_t *wx;
        if (key->type == wintype_Pair)
        {
            gli_strict_warning("window_set_arrangement: keywin cannot be a Pair");
            return;
        }
        for (wx=key; wx; wx=wx->parent)
        {
            if (wx == win)
                break;
        }
        if (wx == NULL)
        {
            gli_strict_warning("window_set_arrangement: keywin must be a descendant");
            return;
        }
    }

    dwin = win->data;

    newdir = method & winmethod_DirMask;
    newvertical = (newdir == winmethod_Left || newdir == winmethod_Right);
    newbackward = (newdir == winmethod_Left || newdir == winmethod_Above);
    if (!key)
        key = dwin->key;

    if ((newvertical && !dwin->vertical) || (!newvertical && dwin->vertical))
    {
        if (!dwin->vertical)
            gli_strict_warning("window_set_arrangement: split must stay horizontal");
        else
            gli_strict_warning("window_set_arrangement: split must stay vertical");
        return;
    }

    if (key && key->type == wintype_Blank
        && (method & winmethod_DivisionMask) == winmethod_Fixed)
    {
        gli_strict_warning("window_set_arrangement: a Blank window cannot have a fixed size");
        return;
    }

    if ((newbackward && !dwin->backward) || (!newbackward && dwin->backward))
    {

        window_t *tmpwin = dwin->child1;
        dwin->child1 = dwin->child2;
        dwin->child2 = tmpwin;
    }


    dwin->dir = newdir;
    dwin->division = method & winmethod_DivisionMask;
    dwin->key = key;
    dwin->size = size;
    dwin->wborder = ((method & winmethod_BorderMask) == winmethod_Border);

    dwin->vertical = (dwin->dir == winmethod_Left || dwin->dir == winmethod_Right);
    dwin->backward = (dwin->dir == winmethod_Left || dwin->dir == winmethod_Above);

    gli_windows_rearrange();
}
