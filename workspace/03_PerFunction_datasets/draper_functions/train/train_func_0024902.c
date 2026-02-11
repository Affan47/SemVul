gva_columns_save (GtkTreeView *view)
{
        GSettings *settings;
        GVariantBuilder builder;
        GVariant *variant;
        GSList *list, *iter;

        g_return_if_fail (GTK_IS_TREE_VIEW (view));

        settings = gva_get_settings ();

        g_variant_builder_init (&builder, (GVariantType *) "as");
        list = gva_columns_get_names (view, FALSE);
        for (iter = list; iter != NULL; iter = iter->next)
                g_variant_builder_add (&builder, "s", iter->data);
        variant = g_variant_builder_end (&builder);
        g_slist_free (list);


        g_settings_set_value (settings, GVA_SETTING_ALL_COLUMNS, variant);

        g_variant_builder_init (&builder, (GVariantType *) "as");
        list = gva_columns_get_names (view, TRUE);
        for (iter = list; iter != NULL; iter = iter->next)
                g_variant_builder_add (&builder, "s", iter->data);
        variant = g_variant_builder_end (&builder);
        g_slist_free (list);


        g_settings_set_value (settings, GVA_SETTING_COLUMNS, variant);
}
