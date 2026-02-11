GC_do_parallel_mark()
{
    mse local_mark_stack[LOCAL_MARK_STACK_SIZE];
    mse * local_top;
    mse * my_top;

    GC_acquire_mark_lock();
    GC_ASSERT(I_HOLD_LOCK());


    if (GC_help_wanted || GC_active_count != 0 || GC_helper_count != 0)
	ABORT("Tried to start parallel mark in bad state");
#   ifdef PRINTSTATS
	GC_printf1("Starting marking for mark phase number %lu\n",
		   (unsigned long)GC_mark_no);
#   endif
    GC_first_nonempty = GC_mark_stack;
    GC_active_count = 0;
    GC_helper_count = 1;
    GC_help_wanted = TRUE;
    GC_release_mark_lock();
    GC_notify_all_marker();

    GC_mark_local(local_mark_stack, 0);
    GC_acquire_mark_lock();
    GC_help_wanted = FALSE;

    while (GC_helper_count > 0) GC_wait_marker();

#   ifdef PRINTSTATS
	GC_printf1(
	    "Finished marking for mark phase number %lu\n",
	    (unsigned long)GC_mark_no);
#   endif
    GC_mark_no++;
    GC_release_mark_lock();
    GC_notify_all_marker();
}
