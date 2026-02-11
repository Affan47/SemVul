globus_l_pthread_activate(void)
{
    int rc;
    globus_i_thread_t *thread;

    globus_module_activate(GLOBUS_THREAD_COMMON_MODULE);
    if(globus_l_thread_already_initialized)
    {
        return GLOBUS_SUCCESS;
    }

    globus_l_thread_already_initialized = GLOBUS_TRUE;


    rc = pthread_attr_init(&(globus_thread_all_global_vars.threadattr));
    globus_i_thread_test_rc( rc, _GCSL("GLOBUSTHREAD: pthread_attr_init() failed\n" ));


    rc = pthread_key_create(&(globus_thread_all_global_vars.globus_thread_t_pointer),
                             NULL);
    globus_i_thread_test_rc(rc, _GCSL("GLOBUSTHREAD: pthread_key_create() failed\n"));

    globus_mutex_init(&(thread_mem_mutex),
                      (globus_mutexattr_t *) NULL);


    thread = new_thread();
    set_tsd(thread);

    return GLOBUS_SUCCESS;
}
