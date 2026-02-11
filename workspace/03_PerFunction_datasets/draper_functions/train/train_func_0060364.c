get_next_dlg_mt(Task *task,
                int pg,
                int **list,
                int *list_num)
{
    int i,j;
    int pre_dlg = get_recent_assigned_dlg(task, pg);
    int pre_tlg = get_recent_assigned_tlg(task, pg);

    for (i = 1; i < task->max_tlg + 1; i++) {
        for (j = 0; j < list_num[i]; j++) {
            int ready = list[i][j];
            int tlg_no = task->Tlg_tag[ready];
            int dlg_no = task->Dlg_tag[ready];
            int dlg_pg = get_pc_of_dlg(task, ready);
            int first = ( task->max_dlg[tlg_no] / task->ProNum ) * pg + 1;

            if (pre_tlg == NOT_TLG || pre_tlg != tlg_no) {
                if (dlg_pg == pg && dlg_no == first)
                    return ready;
            } else if (pre_tlg == tlg_no) {
                if (dlg_pg == pg && dlg_no == pre_dlg + 1)
                    return ready;
            }
        }
    }
    return 0;
}
