gwy_data_field_multiply(GwyDataField *data_field, gdouble value)
{
    gint i;
    gdouble *p;

    g_return_if_fail(GWY_IS_DATA_FIELD(data_field));

    p = data_field->data;
    for (i = data_field->xres * data_field->yres; i; i--, p++)
        *p *= value;


    data_field->cached &= CBIT(MIN) | CBIT(MAX) | CBIT(SUM) | CBIT(RMS)
                          | CBIT(MED) | CBIT(ARF) | CBIT(ART);
    CVAL(data_field, MIN) *= value;
    CVAL(data_field, MAX) *= value;
    CVAL(data_field, SUM) *= value;
    CVAL(data_field, RMS) *= fabs(value);
    CVAL(data_field, MED) *= value;
    CVAL(data_field, ARF) *= value;
    CVAL(data_field, ART) *= value;
    if (value < 0) {
        GWY_SWAP(gdouble, CVAL(data_field, MIN), CVAL(data_field, MAX));
        GWY_SWAP(gdouble, CVAL(data_field, ARF), CVAL(data_field, ART));
    }
}
