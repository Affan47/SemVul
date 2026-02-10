pick_curves(CutControls *controls)
{
    GwyGraphModel *parent_gmodel, *graph_model;
    gint i;

    graph_model = controls->args->graph_model;
    parent_gmodel = gwy_graph_get_model(controls->args->parent_graph);
    gwy_graph_model_remove_all_curves(graph_model);

    if (!controls->args->is_all) {
        gwy_graph_model_add_curve(graph_model,
                                  gwy_graph_model_get_curve(parent_gmodel,
                                                            controls->args->curve));
    }
    else {
        for (i = 0; i < gwy_graph_model_get_n_curves(parent_gmodel); i++)
            gwy_graph_model_add_curve(graph_model,
                                      gwy_graph_model_get_curve(parent_gmodel,
                                                                i));
    }
    cut_limit_selection(controls, TRUE);
}
