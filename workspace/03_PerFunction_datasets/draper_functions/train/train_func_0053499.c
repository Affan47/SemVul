gwy_container_gis_double(GwyContainer *container,
                         GQuark key,
                         gdouble *value)
{
    GValue *p;

    if ((p = gwy_container_gis_value_of_type(container, key, G_TYPE_DOUBLE))) {
        *value = g_value_get_double(p);
        return TRUE;
    }
    return FALSE;
}
