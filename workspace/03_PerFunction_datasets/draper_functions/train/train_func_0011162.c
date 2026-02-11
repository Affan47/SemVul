find_all_func (gpointer              key,
               gpointer              value,
               HashTableFindAllData *data)
{
        gboolean res;

        res = data->predicate (key, value, data->user_data);
        if (res) {
                data->list = g_list_prepend (data->list, value);
        }
}
