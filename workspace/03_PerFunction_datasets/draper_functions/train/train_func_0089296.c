_gf_set_dict_iter2 (char *val, void *data)
{
        void **dataa      = data;
        gf_boolean_t *boo = dataa[0];
        char *comp        = dataa[1];

        if (match_comp (val, comp))
                *boo = _gf_true;

        return 0;
}
