increase_mtrigger (size_t size, const char *what)
{
  size_t mallocated = 0;
  int overflow = 0, triggered = 0;

  scm_i_pthread_mutex_lock (&scm_i_gc_admin_mutex);
  if (ULONG_MAX - size < scm_mallocated)
    overflow = 1;
  else
    {
      scm_mallocated += size;
      mallocated = scm_mallocated;
      if (scm_mallocated > scm_mtrigger)
	triggered = 1;
    }
  scm_i_pthread_mutex_unlock (&scm_i_gc_admin_mutex);

  if (overflow)
    scm_memory_error ("Overflow of scm_mallocated: too much memory in use.");


  if (triggered)
    {
      unsigned long prev_alloced;
      float yield;

      scm_i_scm_pthread_mutex_lock (&scm_i_sweep_mutex);
      scm_gc_running_p = 1;

      prev_alloced  = mallocated;
      scm_i_gc (what);
      scm_i_sweep_all_segments ("mtrigger");

      yield = (((float) prev_alloced - (float) scm_mallocated)
	       / (float) prev_alloced);

      scm_gc_malloc_yield_percentage = (int) (100  * yield);

#ifdef DEBUGINFO
      fprintf (stderr,  "prev %lud , now %lud, yield %4.2lf, want %d",
	       prev_alloced,
	       scm_mallocated,
	       100.0 * yield,
	       scm_i_minyield_malloc);
#endif

      if (yield < scm_i_minyield_malloc /  100.0)
	{


	  float no_overflow_trigger = scm_mallocated * 110.0;

	  no_overflow_trigger /= (float)  (100.0 - scm_i_minyield_malloc);


	  if (no_overflow_trigger >= (float) ULONG_MAX)
	    scm_mtrigger = ULONG_MAX;
	  else
	    scm_mtrigger =  (unsigned long) no_overflow_trigger;

#ifdef DEBUGINFO
	  fprintf (stderr, "Mtrigger sweep: ineffective. New trigger %d\n",
		   scm_mtrigger);
#endif
	}

      scm_gc_running_p = 0;
      scm_i_pthread_mutex_unlock (&scm_i_sweep_mutex);
    }
}
