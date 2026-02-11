gwy_axis_quantize_normal_tics(gdouble arg, gint guide)
{
    gdouble power = gwy_axis_dbl_raise(10.0, (gint)floor(log10(arg)));
    gdouble xnorm = arg / power;
    gdouble posns = guide / xnorm;
    gdouble tics;
    if (posns > 40)
        tics = 0.05;
    else if (posns > 20)
        tics = 0.1;
    else if (posns > 10)
        tics = 0.2;
    else if (posns > 4)
        tics = 0.5;
    else if (posns > 1)
        tics = 1;
    else if (posns > 0.5)
        tics = 2;
    else if (posns > 0.1)
        tics = 5;
    else
        tics = ceil(xnorm);

    return (tics * power);
}
