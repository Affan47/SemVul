rb_gc_call_finalizer_at_exit()
{
    RVALUE *p, *pend;
    int i;


    if (need_call_final) {
	p = deferred_final_list;
	deferred_final_list = 0;
	finalize_list(p);
	for (i = 0; i < heaps_used; i++) {
	    p = heaps[i].slot; pend = p + heaps[i].limit;
	    while (p < pend) {
		if (FL_TEST(p, FL_FINALIZE)) {
		    FL_UNSET(p, FL_FINALIZE);
		    p->as.basic.klass = 0;
		    run_final((VALUE)p);
		}
		p++;
	    }
	}
    }

    for (i = 0; i < heaps_used; i++) {
	p = heaps[i].slot; pend = p + heaps[i].limit;
	while (p < pend) {
	    if (BUILTIN_TYPE(p) == T_DATA &&
		DATA_PTR(p) && RANY(p)->as.data.dfree) {
		p->as.free.flags = 0;
		if ((long)RANY(p)->as.data.dfree == -1) {
		    RUBY_CRITICAL(free(DATA_PTR(p)));
		}
		else if (RANY(p)->as.data.dfree) {
		    (*RANY(p)->as.data.dfree)(DATA_PTR(p));
		}
	    }
	    else if (BUILTIN_TYPE(p) == T_FILE) {
		p->as.free.flags = 0;
		rb_io_fptr_finalize(RANY(p)->as.file.fptr);
	    }
	    p++;
	}
    }
}
