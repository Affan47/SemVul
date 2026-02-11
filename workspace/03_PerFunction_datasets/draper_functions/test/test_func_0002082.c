sys_link( int sc_num, pid_t pid, pid_state *state )
{

    if( state->state==pid_state::NONE ) {
        PROC_MEM_LOCK();

        state->state=pid_state::RETURN;


        chroot_translate_param( pid, state, 1, false, false, 0 );


        chroot_translate_param( pid, state, 2, false, false, PATH_MAX );
    } else if( state->state==pid_state::RETURN ) {
        state->state=pid_state::NONE;
    }

    return true;
}
