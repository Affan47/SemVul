fluid_settings_value_destroy_func(void* value)
{
    fluid_setting_node_t *node = value;

    switch (node->type) {
    case FLUID_NUM_TYPE:
        delete_fluid_num_setting((fluid_num_setting_t*) value);
        break;
    case FLUID_INT_TYPE:
        delete_fluid_int_setting((fluid_int_setting_t*) value);
        break;
    case FLUID_STR_TYPE:
        delete_fluid_str_setting((fluid_str_setting_t*) value);
        break;
    case FLUID_SET_TYPE:
        delete_fluid_set_setting((fluid_set_setting_t*) value);
        break;
    }
}
