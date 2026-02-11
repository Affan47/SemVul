_PR_InitMW(void)
{
#ifdef WINNT


    PR_ASSERT(sizeof(LONG) == sizeof(PRMWStatus));
    TimerInit();
#endif
    mw_lock = PR_NewLock();
    PR_ASSERT(NULL != mw_lock);
    mw_state = PR_NEWZAP(_PRGlobalState);
    PR_ASSERT(NULL != mw_state);
    PR_INIT_CLIST(&mw_state->group_list);
    max_polling_interval = PR_MillisecondsToInterval(MAX_POLLING_INTERVAL);
}
