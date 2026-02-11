slapi_entry_attr_get_charray_ext( const Slapi_Entry* e, const char *type, int *numVals)
{
    char **parray = NULL;
    Slapi_Attr* attr = NULL;
    int count = 0;
    slapi_entry_attr_find(e, type, &attr);

    if(numVals == NULL){
        return NULL;
    }

    if(attr!=NULL){
        int hint;
        Slapi_Value *v = NULL;

        for (hint = slapi_attr_first_value(attr, &v);
             hint != -1;
             hint = slapi_attr_next_value(attr, hint, &v))
        {
            const struct berval *bvp = slapi_value_get_berval(v);
            char *p = slapi_ch_malloc(bvp->bv_len + 1);

            memcpy(p, bvp->bv_val, bvp->bv_len);
            p[bvp->bv_len]= '\0';
            charray_add(&parray, p);
            count++;
        }
    }
    *numVals = count;

    return parray;
}
