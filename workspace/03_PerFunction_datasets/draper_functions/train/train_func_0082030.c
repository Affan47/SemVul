iemgui_color(void *x, t_iemgui *iemgui, t_symbol *s, int ac, t_atom *av)
{
    iemgui->x_bcol = iemgui_compatible_col(atom_getintarg(0, ac, av));
    if(ac > 2)
    {
        iemgui->x_fcol = iemgui_compatible_col(atom_getintarg(1, ac, av));
        iemgui->x_lcol = iemgui_compatible_col(atom_getintarg(2, ac, av));
    }
    else
        iemgui->x_lcol = iemgui_compatible_col(atom_getintarg(1, ac, av));
    if(glist_isvisible(iemgui->x_glist))
        (*iemgui->x_draw)(x, iemgui->x_glist, IEM_GUI_DRAW_MODE_CONFIG);
}
