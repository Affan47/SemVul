set_task1_syncs_to_task2(Sche_task *task1, Sche_task *task2)
{
    int sync_no;
    Stasche_syncr_table *syncr;
    Stasche_pc_info *pc_info1 = sche_task_get_pc_info(task1);
    Stasche_pc_info *pc_info2 = sche_task_get_pc_info(task2);

    if (pc_info1 == NULL || pc_info2 == NULL
        || pc_info1->syncs == NULL)
        return;

    sync_no = pc_info1->syncs->sync_num;

    for (syncr = pc_info2->syncr;
         syncr != NULL;
         syncr = syncr->next) {
        if (syncr->sync_num == sync_no)
            break;
    }

    if (syncr != NULL) {
        sche_task_append_send(task1, task2);
        sche_task_append_recv(task2, task1);
    }
}
