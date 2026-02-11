gvir_config_domain_get_features(GVirConfigDomain *domain)
{
    GPtrArray *features;

    g_return_val_if_fail(GVIR_CONFIG_IS_DOMAIN(domain), NULL);

    features = g_ptr_array_new();
    gvir_config_object_foreach_child(GVIR_CONFIG_OBJECT(domain), "features",
                                     add_feature, features);
    g_ptr_array_add(features, NULL);

    return (GStrv)g_ptr_array_free(features, FALSE);
}
