glusterd_check_localoption (char *key)
{
        char *completion = NULL;
        struct volopt_map_entry *vmep = NULL;
        int   ret = 0;

        COMPLETE_OPTION(key, completion, ret);
        for (vmep = glusterd_volopt_map; vmep->key; vmep++) {
                if (strcmp (vmep->key, key) == 0) {
                        if ((vmep->type == DOC) ||
                            (vmep->type == NO_DOC))
                                return _gf_true;
                        else
                                return _gf_false;
                }
        }

        return _gf_false;
}
