gnc_kvp_bag_remove_frame (KvpFrame *root, const char *path, KvpFrame *fr)
{
    KvpValue *arr;
    KvpValueType valtype;
    GList *node, *listhead;

    arr = kvp_frame_get_value (root, path);
    valtype = kvp_value_get_type (arr);
    if (KVP_TYPE_FRAME == valtype)
    {
        if (fr == kvp_value_get_frame (arr))
        {
            KvpValue *old_val = kvp_frame_replace_value_nc (root, path, NULL);
            kvp_value_replace_frame_nc (old_val, NULL);
            kvp_value_delete (old_val);
        }
        return;
    }


    if (KVP_TYPE_GLIST != valtype) return;

    listhead = kvp_value_get_glist(arr);
    for (node = listhead; node; node = node->next)
    {
        KvpValue *va = node->data;
        if (fr == kvp_value_get_frame (va))
        {
            listhead = g_list_remove_link (listhead, node);
            g_list_free_1 (node);
            kvp_value_replace_glist_nc (arr, listhead);
            kvp_value_replace_frame_nc (va, NULL);
            kvp_value_delete (va);
            return;
        }
    }
}
