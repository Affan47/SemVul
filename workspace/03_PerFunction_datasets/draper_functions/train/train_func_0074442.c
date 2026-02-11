mca_oob_tcp_create(int kindex, const char *if_name)
{
    mca_oob_tcp_module_t *mod;

    OPAL_OUTPUT_VERBOSE((1, orte_oob_base_framework.framework_output,
                         "%s creating OOB-TCP module for interface %s",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), if_name));
    mod = (mca_oob_tcp_module_t*)malloc(sizeof(mca_oob_tcp_module_t));
    if (NULL == mod) {
        ORTE_ERROR_LOG(ORTE_ERR_OUT_OF_RESOURCE);
        return ORTE_ERR_OUT_OF_RESOURCE;
    }
    mod->if_name = strdup(if_name);

    memcpy(mod, &mca_oob_tcp_module.api, sizeof(mca_oob_tcp_module_api_t));

    mod->if_kidx = kindex;

    OBJ_CONSTRUCT(&mod->addresses, opal_list_t);


    mod->ev_base = orte_event_base;


    opal_pointer_array_set_item(&mca_oob_tcp_component.modules, kindex, mod);
    mca_oob_tcp_component.num_modules++;
    return ORTE_SUCCESS;
}
