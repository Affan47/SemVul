opal_ifindextoflags(int if_index, uint32_t* if_flags)
{
    opal_if_t* intf;

    if (OPAL_SUCCESS != mca_base_framework_open(&opal_if_base_framework, 0)) {
        return OPAL_ERROR;
    }

    for (intf =  (opal_if_t*)opal_list_get_first(&opal_if_list);
        intf != (opal_if_t*)opal_list_get_end(&opal_if_list);
        intf =  (opal_if_t*)opal_list_get_next(intf)) {
        if (intf->if_index == if_index) {
            memcpy(if_flags, &intf->if_flags, sizeof(uint32_t));
            return OPAL_SUCCESS;
        }
    }
    return OPAL_ERROR;
}
