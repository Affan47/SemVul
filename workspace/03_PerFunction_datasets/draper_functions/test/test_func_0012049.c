bng_draw_new(t_bng *x, t_glist *glist)
{
    int xpos=text_xpix(&x->x_gui.x_obj, glist);
    int ypos=text_ypix(&x->x_gui.x_obj, glist);
    t_canvas *canvas=glist_getcanvas(glist);

    sys_vgui(".x%lx.c create rectangle %d %d %d %d -fill #%6.6x -tags %lxBASE\n",
             canvas, xpos, ypos,
             xpos + x->x_gui.x_w, ypos + x->x_gui.x_h,
             x->x_gui.x_bcol, x);
    sys_vgui(".x%lx.c create oval %d %d %d %d -fill #%6.6x -tags %lxBUT\n",
             canvas, xpos+1, ypos+1,
             xpos + x->x_gui.x_w-1, ypos + x->x_gui.x_h-1,
             x->x_flashed?x->x_gui.x_fcol:x->x_gui.x_bcol, x);
    sys_vgui(".x%lx.c create text %d %d -text {%s} -anchor w \
             -font {{%s} -%d %s} -fill #%6.6x -tags [list %lxLABEL label text]\n",
             canvas, xpos+x->x_gui.x_ldx,
             ypos+x->x_gui.x_ldy,
             strcmp(x->x_gui.x_lab->s_name, "empty")?x->x_gui.x_lab->s_name:"",
             x->x_gui.x_font, x->x_gui.x_fontsize, sys_fontweight,
             x->x_gui.x_lcol, x);
    if(!x->x_gui.x_fsf.x_snd_able)
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags [list %lxOUT%d outlet]\n",
             canvas, xpos,
             ypos + x->x_gui.x_h-1, xpos + IOWIDTH,
             ypos + x->x_gui.x_h, x, 0);
    if(!x->x_gui.x_fsf.x_rcv_able)
        sys_vgui(".x%lx.c create rectangle %d %d %d %d -tags [list %lxIN%d inlet]\n",
             canvas, xpos, ypos,
             xpos + IOWIDTH, ypos+1, x, 0);
}
