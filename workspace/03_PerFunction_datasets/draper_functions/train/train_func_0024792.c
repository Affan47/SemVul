jack_params_set_driver(jack_params_handle params, const char * name)
{
    struct list_head * node_ptr;
    struct jack_parameter_container * container_ptr;

    list_for_each(node_ptr, params_ptr->drivers_ptr)
    {
        container_ptr = list_entry(node_ptr, struct jack_parameter_container, siblings);
        if (strcmp(container_ptr->name, name) == 0)
        {
            params_ptr->driver_ptr->symlink = container_ptr;
            params_ptr->driver_set = true;
            return true;
        }
    }

    return false;
}
