vslider_check_height(t_vslider *x, int h)
{
    if(h < IEM_SL_MINSIZE)
        h = IEM_SL_MINSIZE;
    x->x_gui.x_h = h;
    if(x->x_val > (x->x_gui.x_h*100 - 100))
    {
        x->x_pos = x->x_gui.x_h*100 - 100;
        x->x_val = x->x_pos;
    }
    if(x->x_lin0_log1)
        x->x_k = log(x->x_max/x->x_min)/(double)(x->x_gui.x_h - 1);
    else
        x->x_k = (x->x_max - x->x_min)/(double)(x->x_gui.x_h - 1);
}
