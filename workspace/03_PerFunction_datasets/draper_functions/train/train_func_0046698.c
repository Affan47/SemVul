opal_db_base_fetch_pointer(const opal_identifier_t *proc,
                               const char *key,
                               void **data, opal_data_type_t type)
{
    opal_db_active_module_t *mod;
    int rc, i;

    if (!opal_db_base.id_set) {
        return OPAL_ERR_FATAL;
    }


    for(i = 0; i < 2; i++) {
        OPAL_LIST_FOREACH(mod, &opal_db_base.fetch_order, opal_db_active_module_t) {
            if (NULL == mod->module->fetch_pointer) {
                continue;
            }
            if (OPAL_SUCCESS == (rc = mod->module->fetch_pointer(proc, key, data, type))) {
                return OPAL_SUCCESS;
            }


            if (OPAL_ERR_TAKE_NEXT_OPTION != rc) {
                return rc;
            }
        }
    }


    return OPAL_ERR_DATA_VALUE_NOT_FOUND;
}
