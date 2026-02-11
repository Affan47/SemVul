toggle_nonzero(t_toggle *x, t_floatarg f)
{
    if(f != 0.0)
        x->x_nonzero = f;
}
