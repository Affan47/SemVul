insert_shadow_of_occupied_task(Scheduling_info *sche,
                               Scheduling_info *top_sche,
                               int task_num)
{
    int pc_no, no_in_pc;
    Sche_task ****array = scheduling_info_get_sche_task_array(sche);
    Sche_task ***array_cpu = array[PROC_CPU];

    int pc_num = scheduling_info_get_pc_num(sche);

    if (array_cpu == NULL)
        return;

    for (pc_no = 0; pc_no < pc_num; pc_no++) {
        Sche_task *next, *prev = NULL;

        if (array_cpu[pc_no][0] == NULL)
            continue;

        for (no_in_pc = 0; TRUE; no_in_pc++) {
            Sche_task *task = array_cpu[pc_no][no_in_pc];
            Block_info *b = sche_task_get_body_b(task);
            Scheduling_info *sche = sche_task_get_sche(task);

            next = (!sche_task_is_last_in_pc(task)) ?
                array_cpu[pc_no][no_in_pc+1] : NULL;

            if (b != NULL
                && (block_info_get_acc_st(b) == ACC_OCCUPY
                    || block_info_get_acc_st(b) == ACC_CONFLICT))
                    insert_shadow_to_acc_task(task, prev, next,
                                              top_sche, task_num);


            if (sche != NULL)
                insert_shadow_of_occupied_task(sche,
                                               top_sche, task_num);
            if (sche_task_is_last_in_pc(task))
                break;

            prev = task;
        }
    }
}
