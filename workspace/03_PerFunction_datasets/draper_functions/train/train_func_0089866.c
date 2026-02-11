hradio_draw_move(t_hradio *x, t_glist *glist)
{
    t_canvas *canvas=glist_getcanvas(glist);
    int n=x->x_number, i, dx=x->x_gui.x_w, s4=dx/4;
    int yy11=text_ypix(&x->x_gui.x_obj, glist), yy12=yy11+dx;
    int yy21=yy11+s4, yy22=yy12-s4;
    int xx11b=text_xpix(&x->x_gui.x_obj, glist), xx11=xx11b, xx21=xx11b+s4;
    int xx22=xx11b+dx-s4;

    xx11 = xx11b;
    xx21=xx11b+s4;
    xx22=xx11b+dx-s4;
    for(i=0; i<n; i++)
    {
        sys_vgui(".x%lx.c coords %lxBASE%d %d %d %d %d\n",
                 canvas, x, i, xx11, yy11, xx11+dx, yy12);
        sys_vgui(".x%lx.c coords %lxBUT%d %d %d %d %d\n",
                 canvas, x, i, xx21, yy21, xx22, yy22);
        xx11 += dx;
        xx21 += dx;
        xx22 += dx;
    }
    sys_vgui(".x%lx.c coords %lxLABEL %d %d\n",
             canvas, x, xx11b+x->x_gui.x_ldx, yy11+x->x_gui.x_ldy);
    if(!x->x_gui.x_fsf.x_snd_able)
        sys_vgui(".x%lx.c coords %lxOUT%d %d %d %d %d\n",
             canvas, x, 0, xx11b, yy12-1, xx11b + IOWIDTH, yy12);
    if(!x->x_gui.x_fsf.x_rcv_able)
        sys_vgui(".x%lx.c coords %lxIN%d %d %d %d %d\n",
             canvas, x, 0, xx11b, yy11, xx11b + IOWIDTH, yy11+1);
}
