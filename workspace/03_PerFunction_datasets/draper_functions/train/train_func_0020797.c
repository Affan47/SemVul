gli_window_iterate_treeorder(window_t *win)
{
    if (!win)
        return gli_rootwin;

    if (win->type == wintype_Pair)
    {
        window_pair_t *dwin = win->data;
        if (!dwin->backward)
            return dwin->child1;
        else
            return dwin->child2;
    }
    else
    {
        window_t *parwin;
        window_pair_t *dwin;

        while (win->parent)
        {
            parwin = win->parent;
            dwin = parwin->data;
            if (!dwin->backward)
            {
                if (win == dwin->child1)
                    return dwin->child2;
            }
            else
            {
                if (win == dwin->child2)
                    return dwin->child1;
            }
            win = parwin;
        }

        return NULL;
    }
}
