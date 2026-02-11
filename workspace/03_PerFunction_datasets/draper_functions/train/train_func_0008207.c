cfg_del_single_value_mm(config_obj * cfg, const char *class,
                             const char *key)
{
    config_node *node = NULL;
    node = cfg_get_single_value(cfg, class, key);
    if (node != NULL)
    {
        __int_cfg_remove_node(cfg, node);
        cfg_save_delayed(cfg);
        g_log(LOG_DOMAIN, G_LOG_LEVEL_DEBUG,
              "triggered save delay: del: %s, %s", class, key);
    }
}
