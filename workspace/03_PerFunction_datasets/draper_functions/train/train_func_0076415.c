gnc_table_model_get_confirm_handler (TableModel *model,
                                     const char * cell_name)
{
    g_return_val_if_fail (model != NULL, NULL);

    return gnc_table_model_handler_hash_lookup (model->confirm_handlers,
            cell_name);
}
