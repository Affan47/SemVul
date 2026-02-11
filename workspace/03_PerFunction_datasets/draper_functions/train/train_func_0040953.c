select_car_task_on_same_pg_of_dlg(Task *task,
                                  int pcno,
                                  int *list,
                                  int list_num)
{
    int i;

    for (i = 0; i < list_num; i++) {
        int ready = list[i];
        int car_tag = task->Car_tag[ready];
        int car_pgno = task->Pc_of_dlg[car_tag + 1];

        if (in_IntSet(task->cand_pc, car_pgno)) {
            if (task->SelectTask != ready) {
                task->SelectTask = ready;
                task->SelectPro = car_pgno;
                return;
            }
        } else {
            int j;
            for (j = 0; j < task->ProNum; j++) {
                if (in_IntSet(task->cand_pc, j)) {
                    task->SelectTask = ready;
                    task->SelectPro = j;
                    return;
                }
            }
        }
    }
}
