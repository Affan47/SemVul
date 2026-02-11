toggle_draw_config(t_toggle* x, t_glist* glist)
{
    t_canvas *canvas=glist_getcanvas(glist);

    sys_vgui(".x%lx.c itemconfigure %lxLABEL -font {{%s} -%d %s} -fill #%6.6x -text {%s} \n",
             canvas, x, x->x_gui.x_font, x->x_gui.x_fontsize, sys_fontweight,
             x->x_gui.x_fsf.x_selected?IEM_GUI_COLOR_SELECTED:x->x_gui.x_lcol,
             strcmp(x->x_gui.x_lab->s_name, "empty")?x->x_gui.x_lab->s_name:"");
    sys_vgui(".x%lx.c itemconfigure %lxBASE -fill #%6.6x\n", canvas, x,
             x->x_gui.x_bcol);
    sys_vgui(".x%lx.c itemconfigure %lxX1 -fill #%6.6x\n", canvas, x,
             x->x_on?x->x_gui.x_fcol:x->x_gui.x_bcol);
    sys_vgui(".x%lx.c itemconfigure %lxX2 -fill #%6.6x\n", canvas, x,
             x->x_on?x->x_gui.x_fcol:x->x_gui.x_bcol);
}
