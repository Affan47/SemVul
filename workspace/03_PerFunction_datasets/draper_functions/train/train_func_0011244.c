dict_alloc(gs_ref_memory_t * mem, uint size, ref * pdref)
{
    ref arr;
    int code =
        gs_alloc_ref_array(mem, &arr, a_all, sizeof(dict) / sizeof(ref),
                           "dict_alloc");
    dict *pdict;
    ref dref;

    if (code < 0)
        return code;
    pdict = (dict *) arr.value.refs;
    make_tav(&dref, t_dictionary,
             r_space(&arr) | imemory_new_mask(mem) | a_all,
             pdict, pdict);
    make_struct(&pdict->memory, avm_foreign, mem);
    code = dict_create_contents(size, &dref, dict_default_pack);
    if (code < 0) {
        gs_free_ref_array(mem, &arr, "dict_alloc");
        return code;
    }
    *pdref = dref;
    return 0;
}
