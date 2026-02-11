neural_train_load_args(GwyContainer *settings,
                       NeuralTrainArgs *args)
{
    const guchar *name = GWY_NEURAL_NETWORK_UNTITLED;

    gwy_clear(args, 1);
    args->preview_type = PREVIEW_MODEL;
    args->trainsteps = trainsteps_default;
    args->masking = masking_default;

    gwy_container_gis_int32_by_name(settings, trainsteps_key,
                                    &args->trainsteps);
    gwy_container_gis_enum_by_name(settings, masking_key,
                                   &args->masking);
    neural_train_sanitize_args(args);

    if ((args->nn = gwy_inventory_get_item(gwy_neural_networks(), name)))
        return;

    args->nn = gwy_neural_networks_create_untitled();
    gwy_neural_network_save(args->nn);
}
