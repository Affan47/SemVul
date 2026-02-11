get_discard_last_dtu_timing_param(Task *task,
                                  Block *block_head,
                                  Dtu_parameter *param,
                                  const int pgno)
{
    Block *kick = search_block_from_no(block_head, param->kick_mt.mt_no);
    Cmp_localize_group_info *group_info;
    int entry = param->dt_info->src_sem->entry;
    int assigns = 0;
    int i;

    group_info = get_group_info_entry(kick->cmp_localize, entry);

    for (i = 0; i < task->assigns[pgno]; i++) {
        if (in_IntSet(group_info->array_access_block[entry],
                      task->assign[pgno][i])) {
            assigns = i;
        }
    }

    return get_dtu_mt(task->assign[pgno][assigns], DTU_POST);
}
