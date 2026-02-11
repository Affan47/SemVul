text_vis(t_gobj *z, t_glist *glist, int vis)
{
    t_text *x = (t_text *)z;
    if (vis)
    {
        if (gobj_shouldvis(&x->te_g, glist))
        {
            t_rtext *y = glist_findrtext(glist, x);
            if (x->te_type == T_ATOM)
                glist_retext(glist, x);
            text_drawborder(x, glist, rtext_gettag(y),
                rtext_width(y), rtext_height(y), 1);
            rtext_draw(y);
        }
    }
    else
    {
        t_rtext *y = glist_findrtext(glist, x);
        if (gobj_shouldvis(&x->te_g, glist))
        {
            text_eraseborder(x, glist, rtext_gettag(y));
            rtext_erase(y);
        }
    }
}
