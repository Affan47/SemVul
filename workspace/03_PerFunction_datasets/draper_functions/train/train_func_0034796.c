vu_draw_erase(t_vu* x,t_glist* glist)
{
    int i;
    t_canvas *canvas=glist_getcanvas(glist);

    sys_vgui(".x%lx.c delete %lxBASE\n", canvas, x);
    for(i=1; i<=IEM_VU_STEPS; i++)
    {
        sys_vgui(".x%lx.c delete %lxRLED%d\n", canvas, x, i);
        if(((i+2)&3) && (x->x_scale))
            sys_vgui(".x%lx.c delete %lxSCALE%d\n", canvas, x, i);
    }
    if(x->x_scale)
    {
        i=IEM_VU_STEPS+1;
        sys_vgui(".x%lx.c delete %lxSCALE%d\n", canvas, x, i);
    }
    sys_vgui(".x%lx.c delete %lxPLED\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxRCOVER\n", canvas, x);
    sys_vgui(".x%lx.c delete %lxLABEL\n", canvas, x);
    if(!x->x_gui.x_fsf.x_snd_able)
    {
        sys_vgui(".x%lx.c delete %lxOUT%d\n", canvas, x, 0);
        sys_vgui(".x%lx.c delete %lxOUT%d\n", canvas, x, 1);
    }
    if(!x->x_gui.x_fsf.x_rcv_able)
    {
        sys_vgui(".x%lx.c delete %lxIN%d\n", canvas, x, 0);
        sys_vgui(".x%lx.c delete %lxIN%d\n", canvas, x, 1);
    }
}
