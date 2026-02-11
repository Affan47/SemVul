find_container(struct jack_parameter_container * parent_ptr, const char * const * address, int max_depth)
{
    struct list_head * node_ptr;
    struct jack_parameter_container * container_ptr;

    if (max_depth == 0 || *address == NULL)
    {
        return parent_ptr;
    }

    if (parent_ptr->leaf)
    {
        return NULL;
    }

    if (max_depth > 0)
    {
        max_depth--;
    }

    list_for_each(node_ptr, &parent_ptr->children)
    {
        container_ptr = list_entry(node_ptr, struct jack_parameter_container, siblings);
        if (strcmp(container_ptr->name, *address) == 0)
        {
            if (container_ptr->symlink != NULL)
            {
                container_ptr = container_ptr->symlink;
            }

            return find_container(container_ptr, address + 1, max_depth);
        }
    }

    return NULL;
}
