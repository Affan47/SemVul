orte_rml_oob_del_exception(orte_rml_exception_callback_t cbfunc)
{
    opal_list_item_t *item;

    for (item = opal_list_get_first(&orte_rml_oob_module.exceptions) ;
         item != opal_list_get_end(&orte_rml_oob_module.exceptions) ;
         item = opal_list_get_next(item)) {
        orte_rml_oob_exception_t *ex = (orte_rml_oob_exception_t*) item;

        if (cbfunc == ex->cbfunc) {
            opal_list_remove_item(&orte_rml_oob_module.exceptions, item);
            return ORTE_SUCCESS;
        }
    }
    return ORTE_ERR_NOT_FOUND;
}
