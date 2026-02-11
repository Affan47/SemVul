favorites_save (void)
{
        GSettings *settings;
        GVariantBuilder builder;
        GVariant *variant;
        GList *iter;

        settings = gva_get_settings ();

        g_variant_builder_init (&builder, (GVariantType *) "as");
        for (iter = favorites; iter != NULL; iter = iter->next)
                g_variant_builder_add (&builder, "s", iter->data);
        variant = g_variant_builder_end (&builder);


        g_settings_set_value (settings, GVA_SETTING_FAVORITES, variant);
}
