get_base_tlg(List *tlg_list, IntSet tlg_set)
{
    Tlg *base = NULL;
    int base_size = -1;
    List *li;

    for (li = tlg_list; li != NULL; li = li->next) {
        Tlg *tlg = li->data;
        int size = tlg->total_data_size;

        if (!in_IntSet(tlg_set, tlg->no))
            continue;

        if (size > base_size) {
            base = tlg;
            base_size = tlg->total_data_size;
        } else if (size == base_size) {
            int base_aa_num = list_length(base->align_array_list);
            int aa_num = list_length(tlg->align_array_list);
            if (aa_num > base_aa_num) {
                base = tlg;
                base_size = tlg->total_data_size;
            }
        }
    }
    if (!empty_IntSet(tlg_set))
        remove1_IntSet(tlg_set, base->no);

    return base;
}
