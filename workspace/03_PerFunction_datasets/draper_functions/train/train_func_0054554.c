gwy_tool_spectro_data_switched(GwyTool *gwytool,
                               GwyDataView *data_view)
{
    GwyPlainTool *plain_tool;
    GwyToolSpectro *tool;
    gboolean ignore;

    plain_tool = GWY_PLAIN_TOOL(gwytool);
    tool = GWY_TOOL_SPECTRO(gwytool);
    ignore = (data_view == plain_tool->data_view);

    if (plain_tool->init_failed)
        return;

    if (!ignore) {
        gwy_debug("disconect obj-chosen handler: %u",
                  (guint)tool->layer_object_chosen_id);
        gwy_signal_handler_disconnect(plain_tool->layer,
                                      tool->layer_object_chosen_id);
    }

    GWY_TOOL_CLASS(gwy_tool_spectro_parent_class)->data_switched(gwytool,
                                                                 data_view);
    if (ignore)
        return;

    if (plain_tool->layer) {
        gwy_object_set_or_reset(plain_tool->layer,
                                tool->layer_type,
                                "editable", FALSE,
                                "point-numbers", TRUE,
                                "focus", -1,
                                NULL);
    }
    if (data_view) {
        tool->layer_object_chosen_id =
                g_signal_connect(G_OBJECT(plain_tool->layer),
                                 "object-chosen",
                                 G_CALLBACK(gwy_tool_spectro_object_chosen),
                                 tool);
    }

    gwy_graph_model_remove_all_curves(tool->gmodel);

    if (plain_tool->data_field && tool->spectra) {
        guint nspec = gwy_spectra_get_n_spectra(tool->spectra);
        gwy_selection_set_max_objects(plain_tool->selection, nspec);
        gwy_tool_spectro_fill_locations(tool);
    }
}
