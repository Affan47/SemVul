gwy_caldata_get_size(GObject *obj)
{
    GwyCalData *caldata;

    gwy_debug("");
    g_return_val_if_fail(GWY_IS_CALDATA(obj), 0);

    caldata = GWY_CALDATA(obj);
    if (!caldata->si_unit_x)
        caldata->si_unit_x = gwy_si_unit_new("");
    if (!caldata->si_unit_y)
        caldata->si_unit_y = gwy_si_unit_new("");
    if (!caldata->si_unit_z)
        caldata->si_unit_z = gwy_si_unit_new("");
    {
        GwySerializeSpec spec[] = {
            { 'i', "ndata", &caldata->ndata, NULL, },
            { 'o', "si_unit_x", &caldata->si_unit_x, NULL, },
            { 'o', "si_unit_y", &caldata->si_unit_y, NULL, },
            { 'o', "si_unit_z", &caldata->si_unit_z, NULL, },
            { 'd', "x_from", &caldata->x_from, NULL, },
            { 'd', "y_from", &caldata->y_from, NULL, },
            { 'd', "z_from", &caldata->z_from, NULL, },
            { 'd', "x_to", &caldata->x_to, NULL, },
            { 'd', "y_to", &caldata->y_to, NULL, },
            { 'd', "z_to", &caldata->z_to, NULL, },
            { 'D', "x", &caldata->x, &caldata->ndata, },
            { 'D', "y", &caldata->y, &caldata->ndata, },
            { 'D', "z", &caldata->z, &caldata->ndata, },
            { 'D', "xerr", &caldata->xerr, &caldata->ndata, },
            { 'D', "yerr", &caldata->yerr, &caldata->ndata, },
            { 'D', "zerr", &caldata->zerr, &caldata->ndata, },
            { 'D', "xunc", &caldata->xunc, &caldata->ndata, },
            { 'D', "yunc", &caldata->yunc, &caldata->ndata, },
            { 'D', "zunc", &caldata->zunc, &caldata->ndata, },
        };

        return gwy_serialize_get_struct_size(GWY_CALDATA_TYPE_NAME,
                                             G_N_ELEMENTS(spec), spec);
    }
}
