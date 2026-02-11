glist_deselectline(t_glist *x)
{
    if (x->gl_editor)
    {
        x->gl_editor->e_selectedline = 0;
        sys_vgui(".x%lx.c itemconfigure l%lx -fill black\n",
            x, x->gl_editor->e_selectline_tag);
    }
}
