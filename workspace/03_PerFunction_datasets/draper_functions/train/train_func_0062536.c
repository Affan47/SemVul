gwy_data_line_copy(GwyDataLine *a, GwyDataLine *b)
{
    g_return_if_fail(a->res == b->res);

    memcpy(b->data, a->data, a->res*sizeof(gdouble));
}
