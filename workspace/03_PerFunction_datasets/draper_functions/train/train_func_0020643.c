GC_call_with_gc_active(GC_fn_type fn,
                                             void * client_data)
{
    struct GC_traced_stack_sect_s stacksect;
    GC_ASSERT(GC_is_initialized);


    if ((word)GC_stackbottom HOTTER_THAN (word)(&stacksect))
      GC_stackbottom = (ptr_t)(&stacksect);

    if (GC_blocked_sp == NULL) {

      client_data = fn(client_data);

      GC_noop1((word)(&stacksect));
      return client_data;
    }


    stacksect.saved_stack_ptr = GC_blocked_sp;
#   ifdef IA64

      stacksect.backing_store_end = GC_save_regs_in_stack();


      stacksect.saved_backing_store_ptr = GC_blocked_register_sp;
#   endif
    stacksect.prev = GC_traced_stack_sect;
    GC_blocked_sp = NULL;
    GC_traced_stack_sect = &stacksect;

    client_data = fn(client_data);
    GC_ASSERT(GC_blocked_sp == NULL);
    GC_ASSERT(GC_traced_stack_sect == &stacksect);


    GC_traced_stack_sect = stacksect.prev;
#   ifdef IA64
      GC_blocked_register_sp = stacksect.saved_backing_store_ptr;
#   endif
    GC_blocked_sp = stacksect.saved_stack_ptr;

    return client_data;
}
