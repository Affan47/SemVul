make_array_size_list(List *aduts_list,
                     List *aa_list,
                     Module_table *module)
{
    Array_def_use_table_semnode *aduts;
    AlignArray *aa;
    Array_size *as;
    List *li, *ret = NULL;

    for (li = aduts_list; li != NULL; li = li->next) {
        aduts = li->data;
        aa = get_aduts_align_array(aduts, aa_list);
        if (aa != NULL) {
            as = construct_array_size(aduts, aa, module);
            ret = list_append(ret, as);
        }
    }

    return ret;
}
