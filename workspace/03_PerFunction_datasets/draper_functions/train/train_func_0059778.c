profile_exit( profile_frame * frame )
{
    if ( DEBUG_PROFILE )
    {

        clock_t const t = clock() - frame->entry_time - frame->overhead;


        if ( frame->info->stack_count == 1 )
            frame->info->cumulative += t;


        frame->info->net += t - frame->subrules;

        if ( frame->caller )
        {

            frame->caller->overhead += frame->overhead;
            frame->caller->subrules += t;
        }

        --frame->info->stack_count;
        profile_stack = frame->caller;
    }
}
