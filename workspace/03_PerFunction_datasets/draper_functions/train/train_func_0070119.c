__int_cfg_get_single_value_as_string(config_obj * cfg,
                                                  const char *class,
                                                  const char *key)
{
    config_node *cur = cfg_get_single_value(cfg, class, key);
    if (cur != NULL)
    {
        if (cur->type == TYPE_ITEM)
        {
            return g_strdup((char *)cur->value);
        }
    }
    return NULL;
}
