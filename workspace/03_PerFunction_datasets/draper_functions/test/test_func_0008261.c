gwy_axis_normalscale(GwyAxis *a)
{
    gint i;
    GwyAxisTick mit;
    GwyAxisLabeledTick mjt;
    gdouble reqmin, reqmax;
    gdouble range, tickstep, majorbase, minortickstep, minorbase;


    reqmin = MIN(a->reqmin, a->reqmax);
    reqmax = MAX(a->reqmax, a->reqmin);
    if (reqmax == reqmin) {
        if (reqmax == 0.0) {
            reqmin = 0.0;
            reqmax = 1.0;
        }
        else {
            range = fabs(reqmax);
            reqmax += range/2.0;
            reqmin -= range/2.0;
        }
    }
    gwy_debug("%p: reqmin: %g, reqmax: %g", a, reqmin, reqmax);

    range = fabs(reqmax - reqmin);

    if (range > G_MAXDOUBLE/100.0 || range < -G_MAXDOUBLE/100.0) {
        g_warning("Axis with extreme range!");
        return TRUE;
    }


    tickstep = gwy_axis_quantize_normal_tics(range, a->par.major_maxticks);
    majorbase = ceil(reqmin/tickstep)*tickstep;
    minortickstep = tickstep/(gdouble)a->par.minor_division;
    minorbase = ceil(reqmin/minortickstep)*minortickstep;
    gwy_debug("majorbase: %g, tickstep: %g, minorbase: %g: minortickstep %g",
              majorbase, tickstep, minorbase, minortickstep);
    if (majorbase > reqmin) {
        majorbase -= tickstep;
        minorbase = majorbase;
        a->min = majorbase;
    }
    else
        a->min = reqmin;


    i = 0;
    do {
        mjt.t.value = majorbase;
        mjt.ttext = g_string_new(NULL);
        a->mjticks = g_array_append_val(a->mjticks, mjt);
        majorbase += tickstep;
        i++;
    } while ((majorbase - tickstep) < reqmax && i < 2*a->par.major_maxticks);
    a->max = majorbase - tickstep;


    i = 0;

    do {
        mit.value = minorbase;
        a->miticks = g_array_append_val(a->miticks, mit);
        minorbase += minortickstep;
        i++;
    } while (minorbase <= a->max && i < 20*a->par.major_maxticks);

    gwy_debug("min: %g, max: %g", a->min, a->max);

    return TRUE;
}
