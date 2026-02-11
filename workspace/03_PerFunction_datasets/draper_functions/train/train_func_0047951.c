fluid_settings_add_option(fluid_settings_t* settings, const char *name, const char *s)
{
    fluid_setting_node_t *node;
    int retval = 0;

    fluid_return_val_if_fail (settings != NULL, 0);
    fluid_return_val_if_fail (name != NULL, 0);
    fluid_return_val_if_fail (name[0] != '\0', 0);
    fluid_return_val_if_fail (s != NULL, 0);

    fluid_rec_mutex_lock (settings->mutex);

    if (fluid_settings_get(settings, name, &node)
        && (node->type == FLUID_STR_TYPE)) {
        fluid_str_setting_t* setting = (fluid_str_setting_t*) node;
        char* copy = FLUID_STRDUP(s);
        setting->options = fluid_list_append(setting->options, copy);
        setting->hints |= FLUID_HINT_OPTIONLIST;
        retval = 1;
    }

    fluid_rec_mutex_unlock (settings->mutex);

    return retval;
}
