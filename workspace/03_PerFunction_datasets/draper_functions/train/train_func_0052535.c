component_shutdown(void)
{
    mca_oob_tcp_module_t *mod;
    int i;
    opal_list_item_t *item;

    opal_output_verbose(2, orte_oob_base_framework.framework_output,
                        "%s TCP SHUTDOWN",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));

    if (ORTE_PROC_IS_HNP && mca_oob_tcp_component.listen_thread_active) {
        mca_oob_tcp_component.listen_thread_active = 0;
        opal_thread_join(&mca_oob_tcp_component.listen_thread, NULL);
    }

    while (NULL != (item = opal_list_remove_first(&mca_oob_tcp_component.listeners))) {
        OBJ_RELEASE(item);
    }


    for (i=0; i < mca_oob_tcp_component.modules.size; i++) {
        if (NULL == (mod = (mca_oob_tcp_module_t*)opal_pointer_array_get_item(&mca_oob_tcp_component.modules, i))) {
            continue;
        }
        if (NULL != mod->api.finalize) {
            mod->api.finalize((struct mca_oob_tcp_module_t*)mod);
        }
    }
}
