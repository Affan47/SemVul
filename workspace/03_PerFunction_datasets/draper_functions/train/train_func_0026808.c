set_pred_and_succ_in_dep_info(Block *layer_block, Dep_info **pp)
{
    int no, total_num = layer_block->mt_num;
    IntSet t;

    construct_IntSet(t, total_num+1);

    for (no = 1; no <= total_num; no++) {
        IntSet cd_pred_set = pp[no]->cd_pred_set;
        IntSet dd_pred_set = pp[no]->dd_pred_set;
        IntSet cd_succ_set = pp[no]->cd_succ_set;
        IntSet dd_succ_set = pp[no]->dd_succ_set;
        int npred, nsucc;
        int *pred = NULL, *succ = NULL;

        or_IntSet(t, cd_pred_set, dd_pred_set);
        npred = number_IntSet(t);
        if (npred > 0) {
            pred = malloc_int_p(npred);
            convert_intset_to_array(t, pred);
        }

        or_IntSet(t, cd_succ_set, dd_succ_set);
        nsucc = number_IntSet(t);
        if (nsucc > 0) {
            succ = malloc_int_p(nsucc);
            convert_intset_to_array(t, succ);
        }

        pp[no]->pred = pred;
        pp[no]->npred = npred;
        pp[no]->succ = succ;
        pp[no]->nsucc = nsucc;
    }

    destruct_IntSet(t);
}
