makefilename_float(t_makefilename *x, t_floatarg f)
{
    char buf[MAXPDSTRING];
    if (x->x_accept == A_FLOAT) {
        if (x->x_intconvert)
            sprintf(buf, x->x_format->s_name, (int)f);
        else sprintf(buf, x->x_format->s_name, f);
    }
    else
    {
        char buf2[MAXPDSTRING];
        sprintf(buf2, "%g", f);
        sprintf(buf, x->x_format->s_name, buf2);
    }
    if (buf[0]!=0)
    outlet_symbol(x->x_obj.ob_outlet, gensym(buf));
}
