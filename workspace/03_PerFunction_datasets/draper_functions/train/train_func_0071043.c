get_depend_syncr_dtu_timing(Task *task,
                            Block *target,
                            Block *bpt,
                            const int tpg,
                            const int ppg)
{
    int i, j;
    Boolean flg = FALSE;
    real lasttime;

    for (i = 0; i < task->assigns[ppg]; i++) {
        int passign = task->assign[ppg][i];

        if (passign == bpt->no) {
            flg = TRUE;
        }
        if (!flg) continue;

        lasttime = task->TaskEndTime[passign];
        for (j = 0; j < task->assigns[tpg]; j++) {
            int tassign = task->assign[tpg][j];
            Block *tblock = task->block[tassign];
            if (task->TaskStartTime[tassign] > lasttime
                && in_IntSet(tblock->pred, bpt->no)) {
                    return get_dtu_mt(tassign, DTU_PRE);
            }
        }
    }

    fatal("Unexpected Situation\n");

    return NULL;
}
