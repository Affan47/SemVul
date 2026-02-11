dict_uid_param(const ref * pdict, gs_uid * puid, int defaultval,
               gs_memory_t * mem, const i_ctx_t *i_ctx_p)
{
    ref *puniqueid;

    if (pdict == 0) {
        uid_set_invalid(puid);
        return defaultval;
    }

    if (level2_enabled &&
        dict_find_string(pdict, "XUID", &puniqueid) > 0
        ) {
        long *xvalues;
        uint size, i;

        if (!r_has_type(puniqueid, t_array))
            return_error(e_typecheck);
        size = r_size(puniqueid);
        if (size == 0)
            return_error(e_rangecheck);
        xvalues = (long *)gs_alloc_byte_array(mem, size, sizeof(long),
                                              "get XUID");

        if (xvalues == 0)
            return_error(e_VMerror);

        for (i = 0; i < size; i++) {
            const ref *pvalue = puniqueid->value.const_refs + i;

            if (!r_has_type(pvalue, t_integer)) {
                gs_free_object(mem, xvalues, "get XUID");
                return_error(e_typecheck);
            }
            xvalues[i] = pvalue->value.intval;
        }
        uid_set_XUID(puid, xvalues, size);
        return 1;
    }


    if (dict_find_string(pdict, "UniqueID", &puniqueid) <= 0) {
        uid_set_invalid(puid);
        return defaultval;
    } else {
        if (!r_has_type(puniqueid, t_integer))
           return_error(e_typecheck);
        if (puniqueid->value.intval < 0 || puniqueid->value.intval > 0xffffff)
           return_error(e_rangecheck);


        if (puniqueid->value.intval == 0) {
            uid_set_invalid(puid);
            return defaultval;
        } else
            uid_set_UniqueID(puid, puniqueid->value.intval);
    }
    return 0;
}
