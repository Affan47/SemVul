div_num_analy_tlg(Hmdf_tlg_info *hti, IntSet tlg_set, int bound)
{
    Tlg *max = hti->max_size_tlg;
    int max_div, div_num;
    List *li;

    max_div = get_max_div_num_tlg(max);
    div_num = set_div_num_tlg(hti, max, bound, max_div);
    add1_IntSet(tlg_set, max->no);

    for (li = hti->tlg_list; li != NULL; li = li->next) {
        Tlg *tlg = li->data;
        LoopDat *lp;

        if (!in_IntSet(tlg_set, tlg->no)) {
            max_div = get_max_div_num_tlg(tlg);
            if (max_div >= div_num) {
                for (lp = tlg->lpdat_head; lp != NULL; lp = lp->next)
                    lp->div_num = div_num;
            } else {
                set_div_num_tlg(hti, tlg, bound, max_div);
            }
            add1_IntSet(tlg_set, tlg->no);
        }
    }

    if (localize_verbose > 0)
        fput_tlg_div_num(stdout, hti, bound);
}
