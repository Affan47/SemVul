sublist_pointer(t_sublist *x, t_gpointer *gp)
{
    t_symbol *templatesym = x->x_templatesym, *dummy;
    t_template *template = template_findbyname(templatesym);
    t_gstub *gs = gp->gp_stub;
    t_word *vec;
    t_getvariable *vp;
    int onset, type;
    t_word *w;

    if (!template)
    {
        pd_error(x, "sublist: couldn't find template %s", templatesym->s_name);
        return;
    }
    if (!gpointer_check(gp, 0))
    {
        pd_error(x, "get: stale or empty pointer");
        return;
    }
    if (!template_find_field(template, x->x_fieldsym,
        &onset, &type, &dummy))
    {
        pd_error(x, "sublist: couldn't find field %s", x->x_fieldsym->s_name);
        return;
    }
    if (type != DT_LIST)
    {
        pd_error(x, "sublist: field %s not of type list", x->x_fieldsym->s_name);
        return;
    }
    if (gs->gs_which == GP_ARRAY) w = gp->gp_un.gp_w;
    else w = gp->gp_un.gp_scalar->sc_vec;

    gpointer_setglist(&x->x_gp, *(t_glist **)(((char *)w) + onset), 0);

    outlet_pointer(x->x_obj.ob_outlet, &x->x_gp);
}
