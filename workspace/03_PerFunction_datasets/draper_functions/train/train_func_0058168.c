hma_state25( int sc_num, pid_t pid, pid_state *state )
{

    if( !ptlib_success( pid, sc_num ) ) {

        dlog( "handle_memory_allocation: " PID_F " procss close failed: %s\n", pid, strerror(ptlib_get_error(pid, sc_num) ) );
    }

    ptlib_set_argument( pid, 1, state->context_state[2]-ptlib_prepare_memory_len() );
    ptlib_set_argument( pid, 2, shared_mem_size );

    ptlib_generate_syscall( pid, SYS_munmap, state->mem->get_shared() );
    return true;
}
