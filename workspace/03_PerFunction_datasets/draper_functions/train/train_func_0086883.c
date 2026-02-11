gnc_gen_trans_update_toggled_cb (GtkCellRendererToggle *cell_renderer,
                                 gchar                 *path,
                                 GNCImportMainMatcher  *gui)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    GNCImportTransInfo *trans_info;

    model = gtk_tree_view_get_model(gui->view);
    if (!gtk_tree_model_get_iter_from_string(model, &iter, path))
        return;
    gtk_tree_model_get(model, &iter, DOWNLOADED_COL_DATA, &trans_info, -1);

    if ( gnc_import_TransInfo_get_action(trans_info) == GNCImport_UPDATE
            && gnc_import_Settings_get_action_skip_enabled (gui->user_settings) == TRUE)
    {
        gnc_import_TransInfo_set_action(trans_info, GNCImport_SKIP);
    }
    else
    {
        gnc_import_TransInfo_set_action(trans_info, GNCImport_UPDATE);
    }
    refresh_model_row(gui, model, &iter, trans_info);
}
