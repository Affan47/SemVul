get_scheduling_info_for_acc_shared(Block_info *block_info,
                                   List *module_info_list,
                                   int *nested_id,
                                   int *nested_pc_no,
                                   int *nested_no_in_pc,
                                   int nest)
{
    Block_info *b2;
    Layer_info *l;
    Block *block;
    Hmdf_table *hmdf;
    Sche_task ***array[PROC_KIND_NUM];
    Scheduling_info *sche;
    List *b_list;

    if (block_info_get_kind(block_info) == SB)
        b2 = block_info_get_callee_info(block_info);
    else
        b2 = block_info;
    l = block_info_get_layer_info(b2);
    block = block_info_get_block(b2);
    hmdf = block->hmdf;

    b_list = layer_info_get_block_info_list(l);

    if (hmdf != NULL) {
        set_sche_task_array_cpu(block,
                                b_list, array,
                                module_info_list,
                                nested_id, nested_pc_no, nested_no_in_pc,
                                nest);
        set_sync_among_sche_task_array_cpu(array, block);

        array[PROC_ACC] = NULL;

        List *dtu_info_list = get_inner_block_info_list_dtu(block);
        set_sche_task_array_dtu_w_sync(block,
                                       dtu_info_list,
                                       array,
                                       module_info_list);

        sche = scheduling_info_new(array, NULL,
                                   hmdf->pc_num, hmdf->pe_num,
                                   0,
                                   hmdf->mtg_id);

        if (block_info_get_kind(block_info) == SB)
            block_info_set_caller_sche(b2, sche);

    } else {
        Hmdf_table *h = get_innermost_hmdf_table_of_outside(block);
        int l = list_length(b_list);

        set_sche_task_array_cpu_by_static_flow(block,
                                               b_list, array,
                                               module_info_list,
                                               nested_id,
                                               nested_pc_no,
                                               nested_no_in_pc,
                                               nest);

        sche = scheduling_info_new(array, array[PROC_CPU][0][l-1],
                                   1, h->pe_num, 0, -1);
    }

    return sche;
}
