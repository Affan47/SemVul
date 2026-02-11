canvas_obj(t_glist *gl, t_symbol *s, int argc, t_atom *argv)
{
    t_text *x;
    if (argc >= 2)
    {
        t_binbuf *b = binbuf_new();
        binbuf_restore(b, argc-2, argv+2);
        canvas_objtext(gl, atom_getintarg(0, argc, argv),
            atom_getintarg(1, argc, argv), 0, b);
    }

    else if (!glist_isvisible(gl))
        post("unable to create stub object in closed canvas!");
    else
    {

        t_binbuf *b = binbuf_new();
        int connectme, xpix, ypix, indx, nobj;
        canvas_howputnew(gl, &connectme, &xpix, &ypix, &indx, &nobj);
        pd_vmess(&gl->gl_pd, gensym("editmode"), "i", 1);
        canvas_objtext(gl, xpix, ypix, 1, b);
        if (connectme)
            canvas_connect(gl, indx, 0, nobj, 0);
        else canvas_startmotion(glist_getcanvas(gl));
    }
}
