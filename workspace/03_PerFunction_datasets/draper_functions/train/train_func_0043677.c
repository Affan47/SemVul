gwy_caldata_finalize(GObject *object)
{
    GwyCalData *caldata = (GwyCalData*)object;

    gwy_object_unref(caldata->si_unit_x);
    gwy_object_unref(caldata->si_unit_y);
    gwy_object_unref(caldata->si_unit_z);

    if (caldata->err_m)
    _gwy_delaunay_mesh_free(caldata->err_m);
    if (caldata->unc_m)
    _gwy_delaunay_mesh_free(caldata->unc_m);


    g_free(caldata->x);
    g_free(caldata->y);
    g_free(caldata->z);
    g_free(caldata->xerr);
    g_free(caldata->yerr);
    g_free(caldata->zerr);
    g_free(caldata->xunc);
    g_free(caldata->yunc);
    g_free(caldata->zunc);

    G_OBJECT_CLASS(gwy_caldata_parent_class)->finalize(object);
}
