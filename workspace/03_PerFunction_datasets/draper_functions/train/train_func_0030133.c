PListEnumerate(PList_t plist, PListFunc_t *user_func, void *user_data)
{
    PListStruct_t *pl = (PListStruct_t *)plist;
    PLValueStruct_t **ppval;
    PLValueStruct_t *pv;
    int i;

    if (!plist) return;

    ppval = (PLValueStruct_t **)(pl->pl_ppval);


    for (i = 0; i < pl->pl_initpi; ++i) {


        pv = ppval[i];
        if (pv) {
            (*user_func)(pv->pv_name, pv->pv_value, user_data);
        }

    }

}
