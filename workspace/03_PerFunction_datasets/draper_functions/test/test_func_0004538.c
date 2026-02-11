glist_findrtext(t_glist *gl, t_text *who)
{
    t_rtext *x;
    if (!gl->gl_editor)
        canvas_create_editor(gl);
    for (x = gl->gl_editor->e_rtext; x && x->x_text != who; x = x->x_next)
        ;
    if (!x) bug("glist_findrtext");
    return (x);
}
