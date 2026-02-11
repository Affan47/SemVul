glist_delete(t_glist *x, t_gobj *y)
{
    t_gobj *g;
    t_object *ob;
    t_gotfn chkdsp = zgetfn(&y->g_pd, gensym("dsp"));
    t_canvas *canvas = glist_getcanvas(x);
    int drawcommand = class_isdrawcommand(y->g_pd);
    int wasdeleting;

    wasdeleting = canvas_setdeleting(canvas, 1);
    if (x->gl_editor)
    {
        if (x->gl_editor->e_grab == y) x->gl_editor->e_grab = 0;
        if (glist_isselected(x, y)) glist_deselect(x, y);


        if (pd_class(&y->g_pd) == canvas_class)
        {
            t_glist *gl = (t_glist *)y;
            if (gl->gl_isgraph)
            {
                char tag[80];
                sprintf(tag, "graph%lx", (t_int)gl);
                glist_eraseiofor(x, &gl->gl_obj, tag);
            }
            else
            {
                if (glist_isvisible(x))
                    text_eraseborder(&gl->gl_obj, x,
                        rtext_gettag(glist_findrtext(x, &gl->gl_obj)));
            }
        }
    }


    if (drawcommand)
        canvas_redrawallfortemplate(template_findbyname(canvas_makebindsym(
            glist_getcanvas(x)->gl_name)), 2);
    gobj_delete(y, x);
    if (glist_isvisible(canvas))
    {
        gobj_vis(y, x, 0);
    }
    if (x->gl_editor && (ob = pd_checkobject(&y->g_pd)))
        rtext_new(x, ob);
    if (x->gl_list == y) x->gl_list = y->g_next;
    else for (g = x->gl_list; g; g = g->g_next)
        if (g->g_next == y)
    {
        g->g_next = y->g_next;
        break;
    }
    pd_free(&y->g_pd);
    if (chkdsp) canvas_update_dsp();
    if (drawcommand)
        canvas_redrawallfortemplate(template_findbyname(canvas_makebindsym(
            glist_getcanvas(x)->gl_name)), 1);
    canvas_setdeleting(canvas, wasdeleting);
    x->gl_valid = ++glist_valid;
}
