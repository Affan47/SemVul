gwy_data_field_new_alike(GwyDataField *model,
                         gboolean nullme)
{
    GwyDataField *data_field;

    g_return_val_if_fail(GWY_IS_DATA_FIELD(model), NULL);
    data_field = g_object_new(GWY_TYPE_DATA_FIELD, NULL);

    data_field->xreal = model->xreal;
    data_field->yreal = model->yreal;
    data_field->xres = model->xres;
    data_field->yres = model->yres;
    data_field->xoff = model->xoff;
    data_field->yoff = model->yoff;
    if (nullme) {
        data_field->data = g_new0(gdouble, data_field->xres*data_field->yres);

        data_field->cached = CBIT(MIN) | CBIT(MAX) | CBIT(SUM) | CBIT(RMS)
                             | CBIT(MED) | CBIT(ARF) | CBIT(ART);

    }
    else
        data_field->data = g_new(gdouble, data_field->xres*data_field->yres);

    if (model->si_unit_xy)
        data_field->si_unit_xy = gwy_si_unit_duplicate(model->si_unit_xy);
    if (model->si_unit_z)
        data_field->si_unit_z = gwy_si_unit_duplicate(model->si_unit_z);

    return data_field;
}
