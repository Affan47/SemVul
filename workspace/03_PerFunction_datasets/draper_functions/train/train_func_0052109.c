gwy_data_field_add(GwyDataField *data_field, gdouble value)
{
    gint i;
    gdouble *p;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));

    p = data_field->data;
    for (i = data_field->xres * data_field->yres; i; i--, p++)
        *p += value;


    data_field->cached &= CBIT(MIN) | CBIT(MAX) | CBIT(SUM) | CBIT(RMS)
                          | CBIT(MED) | CBIT(ARF) | CBIT(ART) | CBIT(ARE);
    CVAL(data_field, MIN) += value;
    CVAL(data_field, MAX) += value;
    CVAL(data_field, SUM) += data_field->xres * data_field->yres * value;

    CVAL(data_field, MED) += value;
    CVAL(data_field, ARF) += value;
    CVAL(data_field, ART) += value;

}
