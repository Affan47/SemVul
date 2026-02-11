gconf_defaults_error_get_type (void)
{
        static GType etype = 0;

        if (etype == 0)
        {
                static const GEnumValue values[] =
                        {
                                ENUM_ENTRY (GCONF_DEFAULTS_ERROR_GENERAL, "GeneralError"),
                                ENUM_ENTRY (GCONF_DEFAULTS_ERROR_NOT_PRIVILEGED, "NotPrivileged"),
                                { 0, 0, 0 }
                        };

                g_assert (GCONF_DEFAULTS_NUM_ERRORS == G_N_ELEMENTS (values) - 1);

                etype = g_enum_register_static ("GConfDefaultsError", values);
        }

        return etype;
}
