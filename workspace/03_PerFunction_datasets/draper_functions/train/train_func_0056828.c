_panel_lockdown_set_property_helper (PanelLockdown *lockdown,
                                     gboolean      *field,
                                     const GValue  *value,
                                     const char    *property)
{
        gboolean new;

        new = g_value_get_boolean (value);
        if (new == *field)
                return;

        *field = new;
        g_object_notify (G_OBJECT (lockdown), property);
}
