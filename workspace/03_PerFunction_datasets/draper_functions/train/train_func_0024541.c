window_binding_window_destroyed (gpointer user_data,
                                 GObject *where_the_object_was)
{
        WindowBinding *binding;

        binding = (WindowBinding *) user_data;
        binding->window = NULL;


        if (binding->sync_timeout_id > 0)
                g_source_remove (binding->sync_timeout_id);

        g_hash_table_remove (bridge->bindings,
                             GUINT_TO_POINTER (binding->id));
}
