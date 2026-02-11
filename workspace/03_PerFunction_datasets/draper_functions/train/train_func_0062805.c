gwy_app_get_any_key_for_id(gint id,
                           const gchar *format,
                           guint nquarks,
                           GQuark *quarks)
{
    GQuark q;

    g_return_val_if_fail(id >= 0, 0);
    if (id < nquarks && quarks[id])
        return quarks[id];

    {
        gchar key[48];

        g_snprintf(key, sizeof(key), format, id);
        q = g_quark_from_string(key);
    }

    if (id < nquarks)
        quarks[id] = q;

    return q;
}
