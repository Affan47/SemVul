gwy_tool_roughness_finalize(GObject *object)
{
    GwyToolRoughness *tool;
    GwyContainer *settings;

    tool = GWY_TOOL_ROUGHNESS(object);

    settings = gwy_app_settings_get();
    gwy_container_set_int32_by_name(settings, thickness_key,
                                    tool->args.thickness);
    gwy_container_set_double_by_name(settings, cutoff_key,
                                     tool->args.cutoff);
    gwy_container_set_enum_by_name(settings, interpolation_key,
                                   tool->args.interpolation);
    gwy_container_set_int32_by_name(settings, expanded_key,
                                    tool->args.expanded);

    g_free(tool->params);
    gwy_object_unref(tool->store);
    gwy_object_unref(tool->dataline);
    gwy_object_unref(tool->slope_unit);
    gwy_si_unit_value_format_free(tool->none_format);

    gwy_object_unref(tool->profiles.texture);
    gwy_object_unref(tool->profiles.waviness);
    gwy_object_unref(tool->profiles.roughness);
    gwy_object_unref(tool->profiles.adf);
    gwy_object_unref(tool->profiles.brc);
    gwy_object_unref(tool->profiles.pc);
    gwy_object_unref(tool->profiles.extline);
    gwy_object_unref(tool->profiles.iin);
    gwy_object_unref(tool->profiles.tmp);
    gwy_object_unref(tool->profiles.rout);
    gwy_object_unref(tool->profiles.iout);


    G_OBJECT_CLASS(gwy_tool_roughness_parent_class)->finalize(object);
}
