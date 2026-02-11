gwy_axis_logscale(GwyAxis *a)
{
    gint i, n;
    gdouble max, min, logmax, logmin, tickstep, base;
    GwyAxisLabeledTick mjt;
    GwyAxisTick mit;

    max = MAX(a->reqmax, a->reqmin);
    min = MIN(a->reqmin, a->reqmax);

    if (min < 0.0 || (min == max && max == 0.0))
        return FALSE;


    logmax = log10(max);
    if (min > 0.0)
        logmin = log10(min);
    else
        logmin = logmax - 1.0;


    n = MAX(a->par.major_maxticks - 1, 1);
    tickstep = (ceil(logmax) - floor(logmin))/n;
    tickstep = ceil(tickstep);
    for (i = 0; i < 3; i++) {
        base = (ceil(logmin/tickstep) - 1)*tickstep;
        if (base <= logmin && base + n*tickstep >= logmax)
            break;
        tickstep += 1.0;
    }
    logmin = base;
    i = 0;
    do {
        mjt.t.value = base;
        mjt.ttext = g_string_new(NULL);
        g_array_append_val(a->mjticks, mjt);
        base += tickstep;
        i++;
    } while (i < 2 || ((base - tickstep) < logmax
                       && i < a->par.major_maxticks));
    logmax = base - tickstep;
    min = gwy_axis_dbl_raise(10.0, logmin);
    max = gwy_axis_dbl_raise(10.0, logmax);


    if (tickstep == 1) {
        tickstep = min;
        base = tickstep;
        i = 0;
        do {

            tickstep = gwy_axis_dbl_raise(10.0, (gint)floor(log10(base*1.001)));
            mit.value = log10(base);
            g_array_append_val(a->miticks, mit);
            base += tickstep;
            i++;
        } while (base <= max && i < a->par.major_maxticks*20);
    }
    else {
        i = 0;
        tickstep = 1;
        base = logmin;
        do {
            mit.value = base;
            g_array_append_val(a->miticks, mit);
            base += tickstep;
            i++;
        } while ((base - tickstep) < logmax && i < a->par.major_maxticks*20);
    }

    a->max = max;
    a->min = min;

    return TRUE;
}
