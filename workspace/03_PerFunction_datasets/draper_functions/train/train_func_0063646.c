fluid_settings_getint(fluid_settings_t* settings, const char *name, int* val)
{
    fluid_setting_node_t *node;
    int retval = 0;

    fluid_return_val_if_fail (settings != NULL, 0);
    fluid_return_val_if_fail (name != NULL, 0);
    fluid_return_val_if_fail (name[0] != '\0', 0);
    fluid_return_val_if_fail (val != NULL, 0);

    fluid_rec_mutex_lock (settings->mutex);

    if (fluid_settings_get(settings, name, &node)
        && (node->type == FLUID_INT_TYPE)) {
        fluid_int_setting_t* setting = (fluid_int_setting_t*) node;
        *val = setting->value;
        retval = 1;
    }

    fluid_rec_mutex_unlock (settings->mutex);

    return retval;
}
