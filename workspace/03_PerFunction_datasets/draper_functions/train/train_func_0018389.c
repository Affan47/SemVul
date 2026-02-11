GC_debug_register_finalizer_unreachable
                                    (void * obj, GC_finalization_proc fn,
                                     void * cd, GC_finalization_proc *ofn,
                                     void * *ocd)
{
    GC_finalization_proc my_old_fn = OFN_UNSET;
    void * my_old_cd;
    ptr_t base = GC_base(obj);
    if (0 == base) {

        if (ocd) *ocd = 0;
        if (ofn) *ofn = 0;
        return;
    }
    if ((ptr_t)obj - base != sizeof(oh)) {
        GC_err_printf(
            "GC_debug_register_finalizer_unreachable called with "
            "non-base-pointer %p\n",
            obj);
    }
    if (0 == fn) {
      GC_register_finalizer_unreachable(base, 0, 0, &my_old_fn, &my_old_cd);
    } else {
      GC_register_finalizer_unreachable(base, GC_debug_invoke_finalizer,
                                        GC_make_closure(fn,cd), &my_old_fn,
                                        &my_old_cd);
    }
    store_old(obj, my_old_fn, (struct closure *)my_old_cd, ofn, ocd);
}
