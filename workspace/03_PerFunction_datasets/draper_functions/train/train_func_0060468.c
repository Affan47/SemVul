listify_counts (gpointer key,
                gpointer val,
                GList **list)
{
        CountData *count_data;
        count_data = g_new0 (CountData, 1);
        count_data->uid = GPOINTER_TO_INT (key);
        count_data->count = GPOINTER_TO_UINT (val);
        *list = g_list_prepend (*list, count_data);
}
