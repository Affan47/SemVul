get_cont_dlg_task(Task *task, int pre_dlg_no)
{
    int i;

    for (i = 0; i < task->cand_tasks; i++) {
        int ready = task->ReadyTask[i];

        if (task->Dlg_tag[ready] != NOT_DLG
            && task->Dlg_tag[ready] == pre_dlg_no)
            return ready;
    }
    return NOT_DLG;
}
