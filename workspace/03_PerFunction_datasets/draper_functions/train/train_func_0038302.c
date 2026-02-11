get_depend_last_dtu_timing(Task *task,
                           Block *block_head,
                           Array_entry_dtu_params *eparams,
                           const int targetpgno)
{
    List *li0, *li1;
    Dtu_parameter *param;
    Dtu_mt *last = NULL;
    real lasttime;
    int i;

    if (eparams == NULL) return NULL;

    for (li0 = eparams->depend; li0 != NULL; li0 = li0->next) {
        param = li0->data;
        for (li1 = param->check_mt; li1 != NULL; li1 = li1->next) {
            Dtu_mt *check = li1->data;
            int pgno = task->TaskexePro[check->mt_no];
            if (pgno == targetpgno) {
                last = get_last_dtu_timing(task, last, check, pgno);
            }
        }
    }

    lasttime = 0;
    for (li0 = eparams->depend; li0 != NULL; li0 = li0->next) {
        param = li0->data;
        if (!have_check_on_pgno(task, param->check_mt, targetpgno)) {
            Block *kick = search_block_from_no(block_head,
                                               param->kick_mt.mt_no);
            if (task->TaskEndTime[kick->no] > lasttime) {
                lasttime = task->TaskEndTime[kick->no];
            }
        }
    }

    if (last != NULL && task->TaskEndTime[last->mt_no] > lasttime) {
        return last;
    }

    for (i = 0; i < task->assigns[targetpgno]; i++) {
        int mtno = task->assign[targetpgno][i];
        if (task->TaskStartTime[mtno] >= lasttime) {
            return get_dtu_mt(mtno, DTU_PRE);
        }
        if (task->TaskEndTime[mtno] >= lasttime) {
            return get_dtu_mt(mtno, DTU_POST);
        }
    }

    fatal("Unexpected Situation\n");

    return NULL;
}
