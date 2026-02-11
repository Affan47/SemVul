make_alg_list(List *ex_tlg_list, Lad_opt *lad_opt)
{
    List *alg_set_list = NULL;
    List *temp_list = NULL;
    List *temp2_list = NULL;
    List *li;
    IntSet temp_set;
    Block *b;
    Alg_set *alg_set;
    int no, tlg_no;
    int most_outer_extlg_no;
    int ex_tlg_list_len;

    temp_set = most_outer_extlg_set(ex_tlg_list);
    temp_list = make_mtg_list(ex_tlg_list);


    ex_tlg_list_len = list_length(ex_tlg_list) + 1;

    while ( number_IntSet(temp_set) > 0){
        most_outer_extlg_no = min_IntSet(temp_set);
        remove1_IntSet(temp_set, most_outer_extlg_no);

        temp2_list =
            make_tlg_list_from_outer_ex_tlg(ex_tlg_list,
                                            temp_list,
                                            most_outer_extlg_no);
        alg_set = construct_alg_set(temp2_list, ex_tlg_list_len, lad_opt);
        if (is_alg_set_connoted_by_another(alg_set_list,
                                           alg_set,
                                           ex_tlg_list_len)) {
            alg_set_list = merge_alg_set(alg_set_list, alg_set, ex_tlg_list_len);
        }
        else {
            alg_set_list = list_append(alg_set_list, alg_set);
        }

        subtract_IntSet(temp_set, temp_set, alg_set->ex_tlg_set);
    }
    destruct_IntSet(temp_set);

    if (localize_verbose > 1) {
        for(li = temp_list; li != NULL; li = li->next){
            for(b = li->data; is_outer_loop_tlg(b); b = b->outer){
                no = get_ex_tlg_no(b, ex_tlg_list);
                tlg_no = get_ex_tlg_no(get_most_outer_loop(b), ex_tlg_list);
                if (no != -1){
                    fprintf(stdout, "extlg_no:%d", no);
                }
                if(tlg_no == no)
                    fprintf(stdout, "\tno %d is most outer tlg set\n", no);
            }
            fprintf(stdout, "\n");
        }
    }


    return (alg_set_list);
}
