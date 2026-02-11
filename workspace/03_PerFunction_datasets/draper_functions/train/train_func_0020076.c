opal_ifkindextoname(int if_kindex, char* if_name, int length)
{
    opal_if_t *intf;

    if (OPAL_SUCCESS != mca_base_framework_open(&opal_if_base_framework, 0)) {
        return OPAL_ERROR;
    }

    for (intf =  (opal_if_t*)opal_list_get_first(&opal_if_list);
        intf != (opal_if_t*)opal_list_get_end(&opal_if_list);
        intf =  (opal_if_t*)opal_list_get_next(intf)) {
        if (intf->if_kernel_index == if_kindex) {
            strncpy(if_name, intf->if_name, length);
            return OPAL_SUCCESS;
        }
    }
    return OPAL_ERROR;
}
