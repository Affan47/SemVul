mask_process(GwyDataField *dfield,
             GwyDataField *maskfield,
             RemoveArgs *args)
{
    GwyDataField *output_field_a, *output_field_b;

    if (args->merge_type == GWY_MERGE_UNION
        || (args->is_height*args->is_area) == 0) {
        if (args->is_height)
            gwy_data_field_grains_remove_by_height(dfield, maskfield,
                                                   args->inverted
                                                   ? 100.0 - args->height
                                                   : args->height,
                                                   args->inverted);
        if (args->is_area)
            gwy_data_field_grains_remove_by_size(maskfield, args->area);
    }
    else {
        output_field_a = gwy_data_field_duplicate(maskfield);
        output_field_b = gwy_data_field_duplicate(maskfield);

        gwy_data_field_grains_remove_by_height(dfield, output_field_a,
                                               args->inverted
                                               ? 100.0 - args->height
                                               : args->height,
                                               args->inverted);
        gwy_data_field_grains_remove_by_size(output_field_b, args->area);

        intersect_removes(output_field_a, output_field_b, maskfield);

        g_object_unref(output_field_a);
        g_object_unref(output_field_b);
    }

    if (args->border)
        gwy_data_field_grains_remove_touching_border(maskfield);
}
