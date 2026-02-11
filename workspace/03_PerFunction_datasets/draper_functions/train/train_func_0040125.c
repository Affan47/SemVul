get_ctrl_task_for_shared_hmdf(Sche_task *sche_task,
                              int pe, int pe_no,
                              Ctrl_task **ctrl_tasks,
                              List *module_info_list)
{
    Block_info *b = sche_task_get_body_b(sche_task);
    Scheduling_info *sche = sche_task_get_sche(sche_task);

    if (block_info_get_kind(b) == SB)
        return get_ctrl_task_for_no_layer_block(b, pe, pe_no,
                                                ctrl_tasks,
                                                module_info_list);
    else
        return get_ctrl_task_for_static_hmdf(b, pe, pe_no, sche,
                                             ctrl_tasks,
                                             module_info_list);
}
