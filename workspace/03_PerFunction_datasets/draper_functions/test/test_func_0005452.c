append_block_set_for_doall(List *block_set_list,
                           Dep_info **dep_array,
                           Hmdf_information *hmdf_info_list,
                           Module_hmdf_information *module_hmdf_info_list,
                           Block *layer_block)
{
    Block *bpt;
    IntSet included_set, block_set;
    int i, l = list_length(block_set_list);
    int total_num = layer_block->mt_num;

    construct_IntSet(included_set, total_num+1);

    for (i = 0; i < l; i++) {
        IntSet set = list_nth_data(block_set_list, i);

        or_IntSet(included_set, included_set, set);
    }

    for (i = 1; i <= total_num; i++) {
        if (in_IntSet(included_set, i))
            continue;

        if (!is_localize_block(dep_array[i]->block,
                               hmdf_info_list,
                               module_hmdf_info_list)
            || dep_array[i]->block->ncfsuc > 1)
            break;
    }

    if (i > total_num)
        return block_set_list;

    for (bpt = layer_block->inner; bpt != NULL; bpt = bpt->next) {
        if (!in_IntSet(included_set, bpt->no)
            && (is_parallel_do_loop(bpt)
                || block_has_tlg_tag(bpt)
                || block_has_dlg_tag(bpt))) {

            construct_IntSet(block_set, total_num+1);
            add1_IntSet(block_set, bpt->no);
            add1_IntSet(included_set, bpt->no);

            add_suc_block_of_doall(bpt->no, block_set, included_set, dep_array,
                                   hmdf_info_list, module_hmdf_info_list);
            add_pre_block_of_doall(bpt->no, block_set, included_set, dep_array,
                                   hmdf_info_list, module_hmdf_info_list);

            block_set_list = list_append(block_set_list, block_set);
        }
    }

    return block_set_list;
}
