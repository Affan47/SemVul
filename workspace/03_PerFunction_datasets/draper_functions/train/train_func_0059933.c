PListInitProp(PList_t plist, int pindex, const char *pname,
              const void *pvalue, PList_t ptype)
{
    int rv;

    if (!plist) return ERRPLUNDEF;


    rv = PListDefProp(plist, pindex, pname, PLFLG_USE_RES);
    if (rv > 0) {


        rv = PListSetValue(plist, rv, pvalue, ptype);
    }

    return rv;
}
