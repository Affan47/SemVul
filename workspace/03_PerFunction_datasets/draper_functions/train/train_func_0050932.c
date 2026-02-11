fit_set_state(FitControls *controls,
              gboolean is_fitted)
{
    FitArgs *args;
    gint i;

    args = controls->args;
    if (!args->is_fitted == !is_fitted)
        return;

    gtk_dialog_set_response_sensitive(GTK_DIALOG(controls->dialog),
                                      RESPONSE_SAVE, is_fitted);

    if (args->is_fitted && !is_fitted) {
        if (gwy_graph_model_get_n_curves(args->graph_model) == 2)
            gwy_graph_model_remove_curve(args->graph_model, 1);

        for (i = 0; i < MAX_PARAMS; i++) {
            gtk_label_set_text(GTK_LABEL(controls->param[i].value), "");
            gtk_label_set_text(GTK_LABEL(controls->param[i].value_unit), "");
            gtk_label_set_text(GTK_LABEL(controls->param[i].error), "");
            gtk_label_set_text(GTK_LABEL(controls->param[i].error_unit), "");
        }
    }
    args->is_fitted = is_fitted;

    if (is_fitted &&
        (gwy_strequal(gwy_cdline_get_name(args->fitfunc),"Circle (down)") ||
        gwy_strequal(gwy_cdline_get_name(args->fitfunc),"Circle (up)")))
        gtk_widget_set_sensitive(controls->draw_circle,TRUE);
    else
        gtk_widget_set_sensitive(controls->draw_circle,FALSE);
}
