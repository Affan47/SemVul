omni_thread_wrapper(void* ptr)
{
    omni_thread* me = (omni_thread*)ptr;

    DB(cerr << "omni_thread_wrapper: thread " << me->id()
       << " started\n");

    THROW_ERRORS(pthread_setspecific(self_key, me));


    if (me->fn_void != NULL) {
	(*me->fn_void)(me->thread_arg);
	omni_thread::exit();
    }

    if (me->fn_ret != NULL) {
	void* return_value = (*me->fn_ret)(me->thread_arg);
	omni_thread::exit(return_value);
    }

    if (me->detached) {
	me->run(me->thread_arg);
	omni_thread::exit();
    } else {
	void* return_value = me->run_undetached(me->thread_arg);
	omni_thread::exit(return_value);
    }


    return NULL;
}
