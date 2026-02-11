set_start_end_time(Stasche *sinfo)
{
    int i, j;
    int *ntasks;
    real *clocks;
    IntSet set;
    Boolean flg;

    ntasks = zcalloc(sinfo->pc_num, sizeof(int));
    clocks = zcalloc(sinfo->pc_num, sizeof(real));
    construct_IntSet(set, sinfo->mt_sum + 1);

    flg = TRUE;
    for (; flg;) {
        flg = FALSE;
        for (i = 0; i < sinfo->pc_num; i++) {
            int mtno = sinfo->sched[i][ntasks[i]];
            Block *b = sinfo->block[mtno];
            if (ntasks[i] < sinfo->ntasks[i]
                && test_subtract_IntSet(sinfo->syncr[mtno], set) == 0) {
                for (j = 1; j < sinfo->mt_num + 1; j++) {
                    if (in_IntSet(sinfo->syncr[mtno], j)
                        && sinfo->end[j] > clocks[i]) {
                        clocks[i] = sinfo->end[j];
                    }
                }
                sinfo->start[mtno] = clocks[i];
                clocks[i] = sinfo->end[mtno] = clocks[i] + b->cost;
                ntasks[i]++;
                add1_IntSet(set, mtno);
            }
            if (ntasks[i] < sinfo->ntasks[i]) {
                flg = TRUE;
            }
        }
    }

    free(ntasks);
    free(clocks);
    destruct_IntSet(set);
}
