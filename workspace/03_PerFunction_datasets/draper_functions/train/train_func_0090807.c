GC_invoke_finalizers()
{
    struct finalizable_object * curr_fo;
    int count = 0;
    word mem_freed_before;
    DCL_LOCK_STATE;

    while (GC_finalize_now != 0) {
#	ifdef THREADS
	    DISABLE_SIGNALS();
	    LOCK();
#	endif
	if (count == 0) {
	    mem_freed_before = GC_mem_freed;
	}
    	curr_fo = GC_finalize_now;
#	ifdef THREADS
 	    if (curr_fo != 0) GC_finalize_now = fo_next(curr_fo);
	    UNLOCK();
	    ENABLE_SIGNALS();
	    if (curr_fo == 0) break;
#	else
	    GC_finalize_now = fo_next(curr_fo);
#	endif
 	fo_set_next(curr_fo, 0);
    	(*(curr_fo -> fo_fn))((ptr_t)(curr_fo -> fo_hidden_base),
    			      curr_fo -> fo_client_data);
    	curr_fo -> fo_client_data = 0;
	++count;
#	ifdef UNDEFINED


    	    GC_free((GC_PTR)curr_fo);
#	endif
    }
    if (count != 0 && mem_freed_before != GC_mem_freed) {
        LOCK();
	GC_finalizer_mem_freed += (GC_mem_freed - mem_freed_before);
	UNLOCK();
    }
    return count;
}
