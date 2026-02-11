vignetting_model_changed(GtkComboBox *widget, preview_data *data)
{
    (void)widget;
    gtk_container_foreach(GTK_CONTAINER(data->LensVignettingTable),
                          delete_children, NULL);

    UFObject *lensfun = ufgroup_element(CFG->ufobject, ufLensfun);
    UFObject *vignetting = ufgroup_element(lensfun, ufVignetting);
    UFObject *model = ufgroup_element(vignetting,
                                      ufobject_string_value(vignetting));
    lfVignettingModel vignettingModel = ufarray_index(vignetting);
    const char *details;
    const lfParameter **params;
    if (!lf_get_vignetting_model_desc(vignettingModel, &details, &params))
        return;
    int i;
    if (params != NULL) {
        for (i = 0; params[i] != NULL; i++) {
            UFObject *param = ufgroup_element(model, params[i]->Name);
            ufnumber_adjustment_scale(param,
                                      GTK_TABLE(data->LensVignettingTable), 0, i,
                                      params[i]->Name, NULL);
            GtkWidget *reset = ufobject_reset_button_new(NULL);
            ufobject_reset_button_add(reset, param);
            gtk_table_attach(GTK_TABLE(data->LensVignettingTable), reset,
                             7, 8, i, i + 1, 0, 0, 0, 0);
        }
    }
    gtk_label_set_text(GTK_LABEL(data->LensVignettingDesc), details);
    gtk_widget_show_all(data->LensVignettingTable);
}
