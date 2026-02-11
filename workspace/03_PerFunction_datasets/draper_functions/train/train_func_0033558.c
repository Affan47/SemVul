remove_cib_op_callback(int call_id, gboolean all_callbacks)
{
    if (all_callbacks) {
        if (cib_op_callback_table != NULL) {
            g_hash_table_destroy(cib_op_callback_table);
        }

        cib_op_callback_table = g_hash_table_new_full(g_direct_hash, g_direct_equal,
                                                      NULL, cib_destroy_op_callback);

    } else {
        g_hash_table_remove(cib_op_callback_table, GINT_TO_POINTER(call_id));
    }
}
