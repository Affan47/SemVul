dict_copy_elements(const ref * pdrfrom  ,
                  ref * pdrto  , int options,
                  dict_stack_t *pds)
{
    int space = r_space(pdrto);
    int index;
    ref elt[2];
    ref *pvslot;
    int code;

    if (space != avm_max) {

        index = dict_first(pdrfrom);
        while ((index = dict_next(pdrfrom, index, elt)) >= 0)
            if (!(options & COPY_NEW_ONLY) ||
                dict_find(pdrto, &elt[0], &pvslot) <= 0
                ) {
                store_check_space(space, &elt[0]);
                store_check_space(space, &elt[1]);
            }
    }

    index = dict_first(pdrfrom);
    while ((index = dict_next(pdrfrom, index, elt)) >= 0) {
        ref *pvalue = pv_no_defn;

        if ((options & COPY_NEW_ONLY) &&
            dict_find(pdrto, &elt[0], &pvslot) > 0
            )
            continue;
        if ((options & COPY_FOR_RESIZE) &&
            r_has_type(&elt[0], t_name) &&
            (pvalue = elt[0].value.pname->pvalue, pv_valid(pvalue))
            )
            elt[0].value.pname->pvalue = pv_no_defn;
        if ((code = dict_put(pdrto, &elt[0], &elt[1], pds)) < 0) {


            if (pvalue != pv_no_defn)
                elt[0].value.pname->pvalue = pvalue;
            return code;
        }
    }
    return 0;
}
