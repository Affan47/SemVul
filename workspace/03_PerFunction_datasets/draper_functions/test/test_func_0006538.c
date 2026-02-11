my_numbox_clip(t_my_numbox *x)
{
    if(x->x_val < x->x_min)
        x->x_val = x->x_min;
    if(x->x_val > x->x_max)
        x->x_val = x->x_max;
}
