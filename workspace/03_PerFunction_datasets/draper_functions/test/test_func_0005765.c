PListAssignValue(PList_t plist, const char *pname,
                 const void *pvalue, PList_t ptype)
{
    PListStruct_t *pl = (PListStruct_t *)plist;
    PLValueStruct_t *pv;
    int pindex;
    int i;

    if (!plist) return ERRPLUNDEF;


    if (pl->pl_symtab) {


        i = PListHashName(pl->pl_symtab, pname);


        for (pv = pl->pl_symtab->pt_hash[i]; pv; pv = pv->pv_next) {

            if (!strcmp(pname, pv->pv_name)) {


                pindex = pv->pv_pi;


                pv->pv_value = (char *)pvalue;


                if (ptype) pv->pv_type = (PListStruct_t *)ptype;


                return pindex;
            }
        }
    }


    return ERRPLUNDEF;
}
