OPL_Timer_StartThread(void)
{
    InitResources();

    timer_thread_state = THREAD_STATE_RUNNING;
    current_time = SDL_GetTicks();
    opl_timer_paused = 0;
    pause_offset = 0;

    timer_thread = SDL_CreateThread(ThreadFunction, NULL);

    if (timer_thread == NULL)
    {
        timer_thread_state = THREAD_STATE_STOPPED;
        FreeResources();

        return 0;
    }

    return 1;
}
