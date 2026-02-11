ListSortIndexHelper(Jim_Obj **lhsObj, Jim_Obj **rhsObj)
{
    Jim_Obj *lObj, *rObj;

    if (Jim_ListIndex(sort_info->interp, *lhsObj, sort_info->index, &lObj, JIM_ERRMSG) != JIM_OK ||
        Jim_ListIndex(sort_info->interp, *rhsObj, sort_info->index, &rObj, JIM_ERRMSG) != JIM_OK) {
        longjmp(sort_info->jmpbuf, JIM_ERR);
    }
    return sort_info->subfn(&lObj, &rObj);
}
