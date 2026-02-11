GC_print_all_errors(void)
{
    static GC_bool printing_errors = FALSE;
    GC_bool have_errors;
    unsigned i;
    DCL_LOCK_STATE;

    LOCK();
    if (printing_errors) {
        UNLOCK();
        return;
    }
    have_errors = GC_have_errors;
    printing_errors = TRUE;
    UNLOCK();

    if (GC_debugging_started) {
      GC_print_all_smashed();
    } else {
      have_errors = FALSE;
    }

    if (GC_n_leaked > 0) {
        GC_err_printf("Found %u leaked objects:\n", GC_n_leaked);
        have_errors = TRUE;
    }
    for (i = 0; i < GC_n_leaked; ++i) {
        ptr_t p = GC_leaked[i];
        GC_print_heap_obj(p);
        GC_free(p);
        GC_leaked[i] = 0;
    }
    GC_n_leaked = 0;

    if (have_errors
#       ifndef GC_ABORT_ON_LEAK
          && GETENV("GC_ABORT_ON_LEAK") != NULL
#       endif
        ) {
      ABORT("Leaked or smashed objects encountered");
    }

    printing_errors = FALSE;
}
