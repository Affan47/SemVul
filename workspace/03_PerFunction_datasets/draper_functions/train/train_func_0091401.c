runTestThread(MprList *groups, MprThread *tp)
{
    MprTestService  *sp;
    MprTestGroup    *gp;
    int             next, i, count;

    sp = MPR->testService;
    mprAssert(sp);

    for (next = 0; (gp = mprGetNextItem(groups, &next)) != 0; ) {
        runInit(gp);
    }
    count = 0;
    for (i = (sp->iterations + sp->numThreads - 1) / sp->numThreads; i > 0; i--) {
        if (sp->totalFailedCount > 0 && !sp->continueOnFailures) {
            break;
        }
        next = 0;
        while ((gp = mprGetNextItem(groups, &next)) != 0) {
            runTestGroup(gp);
        }
        mprPrintf("%12s Iteration %d complete (%s)\n", "[Notice]", ++count, mprGetCurrentThreadName());
    }
    for (next = 0; (gp = mprGetNextItem(groups, &next)) != 0; ) {
        runTerm(gp);
    }
}
