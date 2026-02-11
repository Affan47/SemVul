GC_suspend_handler_inner(ptr_t sig_arg, void *context)
{
    int sig = (int)(word)sig_arg;
    int dummy;
    pthread_t my_thread = pthread_self();
    GC_thread me;
    IF_CANCEL(int cancel_state;)

    AO_t my_stop_count = AO_load(&GC_stop_count);

    if (sig != SIG_SUSPEND) ABORT("Bad signal in suspend_handler");

    DISABLE_CANCEL(cancel_state);


#   ifdef DEBUG_THREADS
      GC_printf("Suspending 0x%x\n", (unsigned)my_thread);
#   endif

    me = GC_lookup_thread(my_thread);


    if (me -> stop_info.last_stop_count == my_stop_count) {

        if (!GC_retry_signals) {
            WARN("Duplicate suspend signal in thread %p\n", pthread_self());
        }
        RESTORE_CANCEL(cancel_state);
        return;
    }
#   ifdef SPARC
        me -> stop_info.stack_ptr = GC_save_regs_in_stack();
#   else
        me -> stop_info.stack_ptr = (ptr_t)(&dummy);
#   endif
#   ifdef IA64
        me -> backing_store_ptr = GC_save_regs_in_stack();
#   endif


    sem_post(&GC_suspend_ack_sem);
    me -> stop_info.last_stop_count = my_stop_count;


    do {
        sigsuspend (&suspend_handler_mask);
    } while (AO_load_acquire(&GC_world_is_stopped)
             && AO_load(&GC_stop_count) == my_stop_count);


#   ifdef DEBUG_THREADS
      GC_printf("Continuing 0x%x\n", (unsigned)my_thread);
#   endif
    RESTORE_CANCEL(cancel_state);
}
