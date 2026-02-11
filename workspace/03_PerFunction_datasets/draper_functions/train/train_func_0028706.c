GC_call_with_gc_active(GC_fn_type fn,
                                             void * client_data)
{
    struct GC_activation_frame_s frame;
    GC_thread me;
    LOCK();
    me = GC_lookup_thread(pthread_self());


    if ((me -> flags & MAIN_THREAD) == 0) {
      GC_ASSERT(me -> stack_end != NULL);
      if (me -> stack_end HOTTER_THAN (ptr_t)(&frame))
        me -> stack_end = (ptr_t)(&frame);
    } else {

      if (GC_stackbottom HOTTER_THAN (ptr_t)(&frame))
        GC_stackbottom = (ptr_t)(&frame);
    }

    if (me -> thread_blocked == FALSE) {

      UNLOCK();
      return fn(client_data);
    }


#   ifdef GC_DARWIN_THREADS

#   else
      frame.saved_stack_ptr = me -> stop_info.stack_ptr;
#   endif
#   ifdef IA64

      frame.backing_store_end = GC_save_regs_in_stack();


      frame.saved_backing_store_ptr = me -> backing_store_ptr;
#   endif
    frame.prev = me -> activation_frame;
    me -> thread_blocked = FALSE;
    me -> activation_frame = &frame;

    UNLOCK();
    client_data = fn(client_data);
    GC_ASSERT(me -> thread_blocked == FALSE);
    GC_ASSERT(me -> activation_frame == &frame);


    LOCK();
    me -> activation_frame = frame.prev;
#   ifdef IA64
      me -> backing_store_ptr = frame.saved_backing_store_ptr;
#   endif
    me -> thread_blocked = TRUE;
#   ifndef GC_DARWIN_THREADS
      me -> stop_info.stack_ptr = frame.saved_stack_ptr;
#   endif
    UNLOCK();

    return client_data;
}
