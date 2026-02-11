canvas_addinlet(t_canvas *x, t_pd *who, t_symbol *s)
{
    t_inlet *ip = inlet_new(&x->gl_obj, who, s, 0);
    if (!x->gl_loading && x->gl_owner && glist_isvisible(x->gl_owner))
    {
        gobj_vis(&x->gl_gobj, x->gl_owner, 0);
        gobj_vis(&x->gl_gobj, x->gl_owner, 1);
        canvas_fixlinesfor(x->gl_owner, &x->gl_obj);
    }
    if (!x->gl_loading) canvas_resortinlets(x);
    return (ip);
}
