AllocReplayBuffers(void)
{
    int i, size = 128, fast = os_avail_mem();

    if(fast < 100000)
        size = 2;
    else if(fast<1000000)
        size = 8;
    else if(fast < 2000000)
        size = 64;
    else if(fast > 4000000)
        size = 256;

    if(highlight) {
        D(bug("Setting replay buffers...\n"));
        size = (highlight_size / 256) + 3;
    }

    CounterLimit = (UWORD)(size * 256 - 1);
    SetLimit = size - 1;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(!(r_controls[i] = malloc(size * 256 * sizeof(LONG)))) {
            D(bug("No memory to allocate r_controls buffers!\n"));
            return FALSE;
        }
    }

    if(!(match = malloc(size * sizeof(struct MatchStatus)))) {
        D(bug("No memory to allocate match buffers!\n"));
        return FALSE;
    }

    if(arcade) {
        if(!(arcade_buf = malloc(size * sizeof(struct pos) * MAX_ARCADE_ON_FIELD))) {
            D(bug("No memory to allocate arcade buffers!\n"));
            return FALSE;
        }
    }


    counter = 0;
    smallcounter = 0;
    ReplaySet = 0;
    replay_mode = FALSE; start_replay = FALSE; was_using_radar = FALSE;
    was_using_nosound = FALSE; was_using_result = FALSE; slow_motion = FALSE;
    mantieni_distanza = FALSE; no_record = FALSE; replay_looped = FALSE;
    full_replay = FALSE; time_stopped = FALSE;

    D(bug("Replay configured: SetLimit:%ld CounterLimit:%ld\n", (LONG)SetLimit, (LONG)CounterLimit));
    return TRUE;
}
