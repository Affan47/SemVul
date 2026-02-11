get_list_cb (QofInstance *inst, gpointer user_data)
{
    struct _get_list_userdata* data = user_data;
    if (!data->is_active_accessor_func || data->is_active_accessor_func(inst, NULL))
        data->result = g_list_prepend(data->result, inst);
}
