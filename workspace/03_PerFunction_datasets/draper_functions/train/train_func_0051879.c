FixModuleRfmArray(void)
{
    RfmArray array;

    for (array = RFM_ModuleCurrent->array_list;
         array != NULL;
         array = array->next) {
        array->entry = (array->prev)?(array->prev->entry + 1):
                                 (RFM_Global->array_num + 1);
        array->is_global = FALSE;
        array->module = RFM_ModuleCurrent;
    }
}
