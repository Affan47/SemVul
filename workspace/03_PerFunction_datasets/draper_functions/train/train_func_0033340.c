globus_l_fork_clean_buffer(
    globus_l_fork_logfile_state_t *     state)
{
    int                                 rc = 0;
    GlobusFuncName(globus_l_fork_clean_buffer);

    SEGForkEnter();


    if (state->buffer != NULL)
    {
        if(state->buffer_point > 0)
        {
            if (state->buffer_valid > 0)
            {
                memmove(state->buffer,
                        state->buffer+state->buffer_point,
                        state->buffer_valid);
            }
            state->buffer_point = 0;
        }
        rc = globus_l_fork_increase_buffer(state);
    }
    SEGForkExit();
    return rc;
}
