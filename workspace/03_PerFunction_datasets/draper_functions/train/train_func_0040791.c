gwy_si_unit_get_size(GObject *obj)
{
    GwySIUnit *si_unit;
    gsize size;

    g_return_val_if_fail(GWY_IS_SI_UNIT(obj), 0);

    si_unit = GWY_SI_UNIT(obj);
    size = gwy_serialize_get_struct_size(GWY_SI_UNIT_TYPE_NAME, 0, NULL);

    size += 20*si_unit->units->len;

    return size;
}
