gwy_gradient_set_from_samples(GwyGradient *gradient,
                              gint nsamples,
                              const guchar *samples,
                              gdouble threshold)
{
    GwyGradientPoint *spoints;
    GList *l, *list = NULL;
    gint i, k;

    g_return_if_fail(GWY_IS_GRADIENT(gradient));
    g_return_if_fail(!GWY_RESOURCE(gradient)->is_const);
    g_return_if_fail(samples);
    g_return_if_fail(nsamples > 0);

    if (threshold < 0)
        threshold = 1.0/80.0;


    spoints = g_new(GwyGradientPoint, MAX(nsamples, 2));
    for (k = i = 0; i < nsamples; i++) {
        spoints[i].x = i/(nsamples - 1.0);
        spoints[i].color.r = samples[k++]/255.0;
        spoints[i].color.g = samples[k++]/255.0;
        spoints[i].color.b = samples[k++]/255.0;
        spoints[i].color.a = samples[k++]/255.0;
    }


    if (nsamples == 1) {
        spoints[0].x = 0.0;
        spoints[1].x = 1.0;
        spoints[1].color = spoints[0].color;
        nsamples = 2;
    }


    list = g_list_append(list, spoints + nsamples-1);
    list = g_list_prepend(list, spoints);
    gwy_gradient_refine_interval(list, nsamples, spoints, threshold);


    g_array_set_size(gradient->points, 0);
    for (l = list; l; l = g_list_next(l)) {
        GwyGradientPoint pt;

        pt = *(GwyGradientPoint*)l->data;
        g_array_append_val(gradient->points, pt);
    }
    g_list_free(list);
    g_free(spoints);
    gwy_gradient_changed(gradient);
}
