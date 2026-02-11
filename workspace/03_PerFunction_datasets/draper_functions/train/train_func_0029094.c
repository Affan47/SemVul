ap_reset_module_loglevels(struct ap_logconf *l, int val)
{
    if (l->module_levels)
        memset(l->module_levels, val, conf_vector_length);
}
