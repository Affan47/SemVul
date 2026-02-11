___stack_limit ___PVOID

#endif
{
  ___processor_state ___ps = ___PSTATE;
  long avail;

#ifdef ___DEBUG_STACK_LIMIT
  ___ps->stack_limit_line = line;
  ___ps->stack_limit_file = file;
  ___printf ("___POLL caused ___stack_limit call at %s:%d\n",
             ___ps->poll_file,
             ___ps->poll_line);
#endif

#ifdef ENABLE_CONSISTENCY_CHECKS
  if (___DEBUG_SETTINGS_LEVEL(___setup_params.debug_settings) >= 1)
    check_fudge_used ();
#endif

  alloc_stack_ptr = ___ps->fp;
  alloc_heap_ptr  = ___ps->hp;

  avail = (heap_size - WORDS_OCCUPIED) / 2;

  if (avail > ___MSECTION_WASTE
#ifdef CALL_GC_FREQUENTLY
      && --___gc_calls_to_punt >= 0
#endif
     )
    {
      if (alloc_stack_ptr < alloc_stack_limit + ___MSECTION_FUDGE)
        {
          ___WORD frame;

          if (alloc_stack_ptr != ___ps->stack_break)
            frame = ___CAST(___WORD,alloc_stack_ptr);
          else
            frame = ___FP_STK(alloc_stack_ptr,-___BREAK_FRAME_NEXT);

          next_stack_msection ();


          ___ps->stack_start = alloc_stack_start;
          alloc_stack_ptr = alloc_stack_start;

          ___FP_ADJFP(alloc_stack_ptr,___BREAK_FRAME_SPACE)
          ___FP_SET_STK(alloc_stack_ptr,-___BREAK_FRAME_NEXT,frame)

          ___ps->stack_break = alloc_stack_ptr;
        }

      setup_pstate ();

      return 0;
    }

  return 1;
}
