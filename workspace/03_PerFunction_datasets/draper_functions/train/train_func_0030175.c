gwy_si_unit_deserialize(const guchar *buffer,
                        gsize size,
                        gsize *position)
{
    gchar *unitstr = NULL;
    GwySerializeSpec spec[] = {
        { 's', "unitstr", &unitstr, NULL, },
    };
    GwySIUnit *si_unit;

    g_return_val_if_fail(buffer, NULL);

    if (!gwy_serialize_unpack_object_struct(buffer, size, position,
                                            GWY_SI_UNIT_TYPE_NAME,
                                            G_N_ELEMENTS(spec), spec)) {
        return NULL;
    }

    if (unitstr && !*unitstr) {
        g_free(unitstr);
        unitstr = NULL;
    }
    si_unit = gwy_si_unit_new(unitstr);
    g_free(unitstr);

    return (GObject*)si_unit;
}
