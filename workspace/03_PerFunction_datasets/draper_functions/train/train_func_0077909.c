sys_sigreturn( int sc_num, pid_t pid, pid_state *state )
{


    if( state->state==pid_state::NONE ) {

        state->state=pid_state::REDIRECT2;
    } else if( state->state==pid_state::REDIRECT2 ) {
        state->state=pid_state::NONE;
    }

    return true;
}
