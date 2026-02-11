sweeper(void *unused, MprThread *tp)
{
    LOG(5, "DEBUG: sweeper thread started");

    MPR->sweeper = 1;
    while (!mprIsStoppingCore()) {
        MPR_MEASURE(7, "GC", "sweep", sweep());
        mprYield(MPR_YIELD_BLOCK);
    }
    MPR->sweeper = 0;
}
