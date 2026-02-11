canvas_msg(t_glist *gl, t_symbol *s, int argc, t_atom *argv)
{
    t_message *x = (t_message *)pd_new(message_class);
    x->m_messresponder.mr_pd = messresponder_class;
    x->m_messresponder.mr_outlet = outlet_new(&x->m_text, &s_float);
    x->m_text.te_width = 0;
    x->m_text.te_type = T_MESSAGE;
    x->m_text.te_binbuf = binbuf_new();
    x->m_glist = gl;
    x->m_clock = clock_new(x, (t_method)message_tick);
    if (argc > 1)
    {
        x->m_text.te_xpix = atom_getfloatarg(0, argc, argv);
        x->m_text.te_ypix = atom_getfloatarg(1, argc, argv);
        if (argc > 2) binbuf_restore(x->m_text.te_binbuf, argc-2, argv+2);
        glist_add(gl, &x->m_text.te_g);
    }
    else if (!glist_isvisible(gl))
        post("unable to create stub message in closed canvas!");
    else
    {
        int connectme, xpix, ypix, indx, nobj;
        canvas_howputnew(gl, &connectme, &xpix, &ypix, &indx, &nobj);

        pd_vmess(&gl->gl_pd, gensym("editmode"), "i", 1);
        x->m_text.te_xpix = xpix;
        x->m_text.te_ypix = ypix;
        glist_add(gl, &x->m_text.te_g);
        glist_noselect(gl);
        glist_select(gl, &x->m_text.te_g);
        gobj_activate(&x->m_text.te_g, gl, 1);
        if (connectme)
            canvas_connect(gl, indx, 0, nobj, 0);
        else canvas_startmotion(glist_getcanvas(gl));
    }
}
