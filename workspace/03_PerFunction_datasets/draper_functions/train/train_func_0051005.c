init_leaf(struct list_head * parent_list_ptr, const char * name, const JSList * params_list, void * obj)
{
    struct jack_parameter_container * container_ptr;

    container_ptr = create_container(parent_list_ptr, name);
    if (container_ptr == NULL)
    {
        return false;
    }

    container_ptr->leaf = true;
    container_ptr->obj = obj;

    while (params_list)
    {
        if (!add_controlapi_param(&container_ptr->children, params_list->data))
        {
            return false;
        }

        params_list = jack_slist_next(params_list);
    }

    return true;
}
