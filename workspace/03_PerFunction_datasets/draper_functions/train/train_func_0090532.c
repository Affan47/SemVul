sys_mkdirat( int sc_num, pid_t pid, pid_state *state )
{
    if( state->state==pid_state::NONE ) {
        PROC_MEM_LOCK();

        chroot_translate_paramat( pid, state, ptlib_get_argument( pid, 1 ), 2, true );

        state->context_state[1]=ptlib_get_argument( pid, 1 );
        state->context_state[2]=ptlib_get_argument( pid, 2 );

        if( log_level>0  ) {
            char name[PATH_MAX];

            ptlib_get_string( pid, state->context_state[2], name, sizeof(name) );
            int fd=(int)state->context_state[1];

            dlog("mkdirat: %d creates %s at %x\n", pid, name, fd );
        }
    }

    return real_mkdir( sc_num, pid, state, 2, PREF_FSTATAT, 0 );
}
