real_open( int sc_num, pid_t pid, pid_state *state, int mode_argnum )
{
    if( state->state==pid_state::NONE ) {
        if( (state->context_state[0]&O_CREAT)!=0 ) {

            state->context_state[1]=ptlib_get_argument( pid, mode_argnum );
            mode_t mode=state->context_state[1];


            mode&=~07000;
            mode|= 00600;

            if( mode!=state->context_state[1] ) {
                ptlib_set_argument( pid, mode_argnum, mode );
            }
        }

        state->state=pid_state::RETURN;
    } else if( state->state==pid_state::RETURN ) {

        if( (state->context_state[0]&O_CREAT)!=0 && ptlib_success(pid, sc_num) ) {
            int fd=(long)ptlib_get_retval(pid);
            dlog("open: " PID_F " opened fd %d, assume we actually created it\n", pid, fd );

            ptlib_save_state( pid, state->saved_state );
            state->state=pid_state::REDIRECT1;


            ptlib_set_argument( pid, 1, fd );
            ptlib_set_argument( pid, 2, state->mem->get_mem() );
            return ptlib_generate_syscall( pid, PREF_FSTAT, state->mem->get_shared() );
        } else
            state->state=pid_state::NONE;
    } else if( state->state==pid_state::REDIRECT2 ) {
        if( ptlib_success( pid, sc_num ) ) {
            ptlib_stat stat;
            stat_override override;

            if( !ptlib_get_mem( pid, state->mem->get_mem(), &stat, sizeof( stat ) ) ) {

                assert(0);
            }


            if( !get_map( stat.dev, stat.ino, &override ) || override.transient ) {

                stat_override_copy( &stat, &override );

                override.uid=state->fsuid;
                override.gid=state->fsgid;
                override.mode&=~07600;
                override.mode|= state->context_state[1]&07600;


                set_map( &override );
                dlog("open: " PID_F " creating override for dev " DEV_F " inode " INODE_F "\n", pid, override.dev, override.inode);
            } else {
                dlog("open: " PID_F " map for dev " DEV_F " inode " INODE_F " already exists - doing nothing\n", pid, stat.dev, stat.ino );
            }
        } else {
            dlog("open: " PID_F " fstat failed %s\n", pid, strerror( ptlib_get_error( pid, sc_num ) ) );
        }

        state->state=pid_state::NONE;
        ptlib_restore_state( pid, state->saved_state );
    }

    return true;
}
