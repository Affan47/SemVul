sysMonitorInit(sys_mon_t *mid)
{
    int ret;

    sysAssert(mid != SYS_MID_NULL);
    ret = mutexInit(&mid->mutex);
    ret = (ret == SYS_OK ? condvarInit(&mid->cv_monitor) : ret);

    mid->entry_count = 0;
    mid->monitor_owner = SYS_THREAD_NULL;
    mid->contention_count = 0;
    INIT_MONITOR_WAIT_QUEUE( mid->mwait_queue );

    return ret;
}
