glist_noselect(t_glist *x)
{
    if (x->gl_editor)
    {
        while (x->gl_editor->e_selection)
            glist_deselect(x, x->gl_editor->e_selection->sel_what);
        if (x->gl_editor->e_selectedline)
            glist_deselectline(x);
    }
}
