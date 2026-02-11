GC_stopped_mark(stop_func)
GC_stop_func stop_func;
{
    register int i;
    int dummy;
#   if defined(PRINTTIMES) || defined(CONDPRINT)
	CLOCK_TYPE start_time, current_time;
#   endif

#   ifdef PRINTTIMES
	GET_TIME(start_time);
#   endif
#   if defined(CONDPRINT) && !defined(PRINTTIMES)
	if (GC_print_stats) GET_TIME(start_time);
#   endif

#   if defined(REGISTER_LIBRARIES_EARLY)
        GC_cond_register_dynamic_libraries();
#   endif
    STOP_WORLD();
    IF_THREADS(GC_world_stopped = TRUE);

	if (GC_notify_event)
		GC_notify_event (GC_EVENT_MARK_START);

#   ifdef CONDPRINT
      if (GC_print_stats) {
	GC_printf1("--> Marking for collection %lu ",
	           (unsigned long) GC_gc_no + 1);
	GC_printf2("after %lu allocd bytes + %lu wasted bytes\n",
	   	   (unsigned long) WORDS_TO_BYTES(GC_words_allocd),
	   	   (unsigned long) WORDS_TO_BYTES(GC_words_wasted));
      }
#   endif
#   ifdef MAKE_BACK_GRAPH
      if (GC_print_back_height) {
        GC_build_back_graph();
      }
#   endif


            GC_clear_a_few_frames();
            GC_noop(0,0,0,0,0,0);
	GC_initiate_gc();
	for(i = 0;;i++) {
	    if ((*stop_func)()) {
#   		    ifdef CONDPRINT
		      if (GC_print_stats) {
		    	GC_printf0("Abandoned stopped marking after ");
			GC_printf1("%lu iterations\n",
				   (unsigned long)i);
		      }
#		    endif
		    GC_deficit = i;
                    IF_THREADS(GC_world_stopped = FALSE);
	            START_WORLD();
	            return(FALSE);
	    }
	    if (GC_mark_some((ptr_t)(&dummy))) break;
	}

    GC_gc_no++;
#   ifdef PRINTSTATS
      GC_printf2("Collection %lu reclaimed %ld bytes",
		  (unsigned long) GC_gc_no - 1,
	   	  (long)WORDS_TO_BYTES(GC_mem_found));
#   else
#     ifdef CONDPRINT
        if (GC_print_stats) {
	  GC_printf1("Collection %lu finished", (unsigned long) GC_gc_no - 1);
	}
#     endif
#   endif
#   ifdef CONDPRINT
      if (GC_print_stats) {
        GC_printf1(" ---> heapsize = %lu bytes\n",
      	           (unsigned long) GC_heapsize);


        GC_printf0("");
      }
#   endif


        if (GC_debugging_started) {
            (*GC_check_heap)();
        }


	if (GC_notify_event)
		GC_notify_event (GC_EVENT_MARK_END);

    IF_THREADS(GC_world_stopped = FALSE);
    START_WORLD();
#   ifdef PRINTTIMES
	GET_TIME(current_time);
	GC_printf1("World-stopped marking took %lu msecs\n",
	           MS_TIME_DIFF(current_time,start_time));
#   else
#     ifdef CONDPRINT
	if (GC_print_stats) {
	  GET_TIME(current_time);
	  GC_printf1("World-stopped marking took %lu msecs\n",
	             MS_TIME_DIFF(current_time,start_time));
	}
#     endif
#   endif
    return(TRUE);
}
