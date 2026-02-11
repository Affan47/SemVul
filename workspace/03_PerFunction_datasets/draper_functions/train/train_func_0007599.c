gnc_sx_get_slr_state_model(void)
{
    if (_singleton_slr_state_model == NULL)
    {
        int i;
        GtkTreeIter iter;

        _singleton_slr_state_model = GTK_TREE_MODEL(gtk_list_store_new(1, G_TYPE_STRING));
        for (i = 0; i != SX_INSTANCE_STATE_CREATED; i++)
        {
            gtk_list_store_insert_with_values(GTK_LIST_STORE(_singleton_slr_state_model),
                                              &iter,
                                              SX_INSTANCE_STATE_MAX_STATE + 1,
                                              0, _(gnc_sx_instance_state_names[i]), -1);
        }
    }
    return _singleton_slr_state_model;
}
