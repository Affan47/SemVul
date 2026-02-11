GC_write_fault_handler(int sig, siginfo_t *si, void *raw_sc)
# endif
{
#   if !defined(MSWIN32) && !defined(MSWINCE)
        char *addr = si -> si_addr;
#   else
        char * addr = (char *) (exc_info -> ExceptionRecord
                                -> ExceptionInformation[1]);
#   endif
    unsigned i;

    if (SIG_OK && CODE_OK) {
        register struct hblk * h =
                        (struct hblk *)((word)addr & ~(GC_page_size-1));
        GC_bool in_allocd_block;
#       ifdef CHECKSUMS
          GC_record_fault(h);
#       endif

#       ifdef SUNOS5SIGS

            in_allocd_block = FALSE;
            for (i = 0; i < divHBLKSZ(GC_page_size); i++) {
              if (HDR(h+i) != 0) {
                in_allocd_block = TRUE;
              }
            }
#       else
            in_allocd_block = (HDR(addr) != 0);
#       endif
        if (!in_allocd_block) {


            SIG_HNDLR_PTR old_handler;

#           if defined(MSWIN32) || defined(MSWINCE)
                old_handler = GC_old_segv_handler;
#           else
                GC_bool used_si;

                if (sig == SIGSEGV) {
                   old_handler = GC_old_segv_handler;
                   used_si = GC_old_segv_handler_used_si;
                } else {
                   old_handler = GC_old_bus_handler;
                   used_si = GC_old_bus_handler_used_si;
                }
#           endif

            if (old_handler == (SIG_HNDLR_PTR)SIG_DFL) {
#               if !defined(MSWIN32) && !defined(MSWINCE)
                    GC_err_printf("Segfault at %p\n", addr);
                    ABORT("Unexpected bus error or segmentation fault");
#               else
                    return(EXCEPTION_CONTINUE_SEARCH);
#               endif
            } else {


#               if defined(MSWIN32) || defined(MSWINCE)
                    return((*old_handler)(exc_info));
#               else
                    if (used_si)
                      ((SIG_HNDLR_PTR)old_handler) (sig, si, raw_sc);
                    else

                      ((PLAIN_HNDLR_PTR)old_handler) (sig);
                    return;
#               endif
            }
        }
        UNPROTECT(h, GC_page_size);


        for (i = 0; i < divHBLKSZ(GC_page_size); i++) {
            size_t index = PHT_HASH(h+i);

            async_set_pht_entry_from_index(GC_dirty_pages, index);
        }


#       if defined(MSWIN32) || defined(MSWINCE)
            return(EXCEPTION_CONTINUE_EXECUTION);
#       else
            return;
#       endif
    }
#if defined(MSWIN32) || defined(MSWINCE)
    return EXCEPTION_CONTINUE_SEARCH;
#else
    GC_err_printf("Segfault at %p\n", addr);
    ABORT("Unexpected bus error or segmentation fault");
#endif
}
