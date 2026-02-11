sys_setresuid( int sc_num, pid_t pid, pid_state *state )
{
    if( state->state==pid_state::NONE ) {

        state->context_state[0]=ptlib_get_argument( pid, 1 );
        state->context_state[1]=ptlib_get_argument( pid, 2 );
        state->context_state[2]=ptlib_get_argument( pid, 3 );


        ptlib_set_syscall( pid, PREF_NOP );
        state->state=pid_state::REDIRECT2;
    } else if( state->state==pid_state::REDIRECT2 ) {

        bool success=true;
        uid_t new_uid=state->uid, new_euid=state->euid, new_suid=state->suid;

        if( state->context_state[0]!=(int_ptr)-1 ) {
            if( check_uids( state->context_state[0], state ) )
                new_uid=state->context_state[0];
            else
                success=false;
        }

        if( state->context_state[1]!=(int_ptr)-1 ) {
            if( success && check_uids( state->context_state[1], state ) )
                new_euid=state->context_state[1];
            else
                success=false;
        }

        if( state->context_state[2]!=(int_ptr)-1 ) {
            if( success && check_uids( state->context_state[2], state ) )
                new_suid=state->context_state[2];
            else
                success=false;
        }


        if( success ) {
            state->uid=new_uid;
            state->euid=new_euid;
            state->suid=new_suid;

            ptlib_set_retval( pid, 0 );
        } else {
            ptlib_set_error( pid, state->orig_sc, EPERM );
        }

        state->state=pid_state::NONE;
    }

    return true;
}
