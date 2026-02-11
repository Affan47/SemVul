wakeup_listener(void)
{
    listener_may_exit = 1;
    if (!listener_os_thread) {


        return;
    }


    ap_queue_info_term(worker_queue_info);


#ifdef HAVE_PTHREAD_KILL
    pthread_kill(*listener_os_thread, LISTENER_SIGNAL);
#else
    kill(ap_my_pid, LISTENER_SIGNAL);
#endif
}
