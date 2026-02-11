opal_db_base_remove_data(const opal_identifier_t *proc,
                             const char *key)
{
    bool did_op;
    opal_db_active_module_t *mod;
    int rc;


    did_op = false;
    OPAL_LIST_FOREACH(mod, &opal_db_base.store_order, opal_db_active_module_t) {
        if (NULL == mod->module->remove) {
            continue;
        }
        if (OPAL_SUCCESS == (rc = mod->module->remove(proc, key))) {
            did_op = true;
            break;
        }


        if (OPAL_ERR_TAKE_NEXT_OPTION != rc) {
            OPAL_ERROR_LOG(rc);
            return rc;
        }
    }


    if (!did_op) {
        OPAL_ERROR_LOG(OPAL_ERROR);
        return OPAL_ERROR;
    }
    return OPAL_SUCCESS;
}
