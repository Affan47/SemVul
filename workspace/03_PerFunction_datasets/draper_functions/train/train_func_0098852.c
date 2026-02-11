fm_module_callback_gtk_folder_col(const char *name, gpointer init, int ver)
{
    if (fm_folder_model_add_custom_column(name, init) == FM_FOLDER_MODEL_COL_DEFAULT)
        return FALSE;
    return TRUE;
}
