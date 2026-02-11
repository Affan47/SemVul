fm_folder_model_set_show_hidden(FmFolderModel* model, gboolean show_hidden)
{
    g_return_if_fail(model != NULL);
    if( model->show_hidden == show_hidden )
        return;
    model->show_hidden = show_hidden;
    fm_folder_model_apply_filters(model);
}
