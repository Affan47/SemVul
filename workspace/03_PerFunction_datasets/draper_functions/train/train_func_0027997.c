__int_cfg_remove_node(config_obj * cfg, config_node * node)
{
    if (node->type != TYPE_ITEM)
    {
        while (node->children)
        {
            __int_cfg_remove_node(cfg, node->children);
        }
    }

    if (node->next == NULL && node->prev == NULL && node->parent)
    {

        if (node->parent->type != TYPE_ITEM)
        {
            node->parent->children = NULL;
        }
    }

    if (node->prev != NULL)
    {
        if (node->parent && node->parent->children == node)
        {
            node->parent->children = node->prev;
        }
        node->prev->next = node->next;
    }
    if (node->next != NULL)
    {
        if (node->parent && node->parent->children == node)
        {
            node->parent->children = node->next;
        }
        node->next->prev = node->prev;
    }
    if (node == cfg->root)
    {
        if (node->prev)
        {
            cfg->root = node->prev;
        } else if (node->next)
        {
            cfg->root = node->next;
        } else
        {
            cfg->root = NULL;
        }
    }
    cfg->total_size -= sizeof(config_node);
    if (node->name)
    {
        cfg->total_size -= strlen(node->name);
        cfg_free_string(node->name);
    }
    if (node->value)
    {
        cfg->total_size -= strlen(node->value);
        cfg_free_string(node->value);
    }
    g_slice_free(config_node, node);
}
