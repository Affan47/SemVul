fluid_settings_option_count (fluid_settings_t *settings, const char *name)
{
    fluid_setting_node_t *node;
    int count = -1;

    fluid_return_val_if_fail (settings != NULL, -1);
    fluid_return_val_if_fail (name != NULL, -1);
    fluid_return_val_if_fail (name[0] != '\0', -1);

    fluid_rec_mutex_lock (settings->mutex);
    if (fluid_settings_get(settings, name, &node) && node->type == FLUID_STR_TYPE)
        count = fluid_list_size (((fluid_str_setting_t *)node)->options);
    fluid_rec_mutex_unlock (settings->mutex);

    return (count);
}
