vu_draw_config(t_vu* x, t_glist* glist)
{
    int i;
    t_canvas *canvas=glist_getcanvas(glist);

    sys_vgui(".x%lx.c itemconfigure %lxBASE -fill #%6.6x\n", canvas, x, x->x_gui.x_bcol);
    for(i=1; i<=IEM_VU_STEPS; i++)
    {
        sys_vgui(".x%lx.c itemconfigure %lxRLED%d -width %d\n", canvas, x, i,
                 x->x_led_size);
        if(((i+2)&3) && (x->x_scale))
            sys_vgui(".x%lx.c itemconfigure %lxSCALE%d -text {%s} -font {{%s} -%d %s} -fill #%6.6x\n",
                     canvas, x, i, iemgui_vu_scale_str[i], x->x_gui.x_font,
                     x->x_gui.x_fontsize, sys_fontweight,
                     x->x_gui.x_fsf.x_selected?IEM_GUI_COLOR_SELECTED:x->x_gui.x_lcol);
    }
    if(x->x_scale)
    {
        i=IEM_VU_STEPS+1;
        sys_vgui(".x%lx.c itemconfigure %lxSCALE%d -text {%s} -font {{%s} -%d %s} -fill #%6.6x\n",
                 canvas, x, i, iemgui_vu_scale_str[i], x->x_gui.x_font,
                 x->x_gui.x_fontsize, sys_fontweight,
                 x->x_gui.x_fsf.x_selected?IEM_GUI_COLOR_SELECTED:x->x_gui.x_lcol);
    }
    sys_vgui(".x%lx.c itemconfigure %lxLABEL -font {{%s} -%d %s} -fill #%6.6x -text {%s} \n",
             canvas, x, x->x_gui.x_font, x->x_gui.x_fontsize, sys_fontweight,
             x->x_gui.x_fsf.x_selected?IEM_GUI_COLOR_SELECTED:x->x_gui.x_lcol,
             strcmp(x->x_gui.x_lab->s_name, "empty")?x->x_gui.x_lab->s_name:"");

    sys_vgui(".x%lx.c itemconfigure %lxRCOVER -fill #%6.6x -outline #%6.6x\n", canvas,
             x, x->x_gui.x_bcol, x->x_gui.x_bcol);
    sys_vgui(".x%lx.c itemconfigure %lxPLED -width %d\n", canvas, x,
             x->x_led_size);
}
