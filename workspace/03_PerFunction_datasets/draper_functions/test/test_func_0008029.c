terminate_thread(globus_i_thread_t *thread,
                 void *status,
                 globus_bool_t really_terminate)
{

    globus_mutex_lock(&thread_mem_mutex);
    thread->next_free = thread_freelist;
    thread_freelist = thread;
    globus_mutex_unlock(&thread_mem_mutex);


    if (really_terminate)
    {
        pthread_exit(NULL);
    }

}
