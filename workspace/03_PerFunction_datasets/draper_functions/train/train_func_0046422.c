sys_mkdir( int sc_num, pid_t pid, pid_state *state )
{
    if( state->state==pid_state::NONE ) {
        PROC_MEM_LOCK();

        chroot_translate_param( pid, state, 1, true );

        state->context_state[1]=ptlib_get_argument( pid, 1 );

        if( log_level>0  ) {
            char name[PATH_MAX];

            ptlib_get_string( pid, state->context_state[0], name, sizeof(name) );

            dlog("mkdir: %d creates %s\n", pid, name );
        }
    }

    return real_mkdir( sc_num, pid, state, 1, PREF_STAT );
}
