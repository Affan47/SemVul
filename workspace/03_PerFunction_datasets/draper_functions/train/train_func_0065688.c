write_barrier_decl_type5(fsbe_context *cx, Module_table *module)
{
    if (get_num_of_barriers(module) > 0) {
        int processer_num = module->super_hmdf->pe_num;
        int decl_num = get_barrier_decl_num_type5(module);

	fsbe_printf(cx, "C == VARIABLE FOR GROUP BARIIER FLAG ==\n");


	ompfbe_iprintf(cx, "INTEGER BARRIER_FLG(%d,0:%d,0:%d)\n",
		       decl_num, processer_num - 1, 2);
#if 0
	if (opt_barrier_delay) {
	    ompfbe_iprintf(cx, "INTEGER DELAY_COUNT\n");
	    ompfbe_iprintf(cx, "VOLATILE DELAY_COUNT\n");
	}
#endif
	if (module->red_head != NULL) {
	    Reduction_table *rpt;
	    Reduction_element *rept;
	    int *count = NULL;
	    int i;
	    int size_of_type = 0;
	    if((count = (int *)calloc(NUM_OF_STR_TYPE, sizeof(int))) == NULL)
		fatal("count allocation error");
	    for (rpt = module->red_head; rpt != NULL; rpt = rpt->next) {
		for (rept = rpt->element_head; rept != NULL; rept = rept->next) {
		    count[(int)rept->type]++;
		}
	    }

	    for (i = 0; i < NUM_OF_STR_TYPE; i++) {
		if (count[i] != 0){
		    switch (i) {
		    case TYPE_INT:
			ompfbe_iprintf(cx, "INTEGER RED_INT");
			size_of_type = sizeof(int);
			break;
		    case TYPE_REAL:
			ompfbe_iprintf(cx, "REAL RED_REAL");
			size_of_type = 8;
                        break;
		    case TYPE_DOUBLE:
			ompfbe_iprintf(cx, "DOUBLE PRECISION RED_DOUBLE");
			size_of_type = sizeof(double);
                        break;
		    case TYPE_LOGICAL:
			ompfbe_iprintf(cx, "LOGICAL RED_LOGICAL");
			size_of_type = 1;
                        break;
		    default:
			fatal("Not implemented type for sync_reduction\n");
			break;
		    }
		    if (size_of_type > 0) {
			if (ompfbe_get_cache_line_size() > 0)
			    fsbe_printf(cx, "(0:%d,0:%d)\n",
					count[i] / (ompfbe_get_cache_line_size() / size_of_type)
					+ (ompfbe_get_cache_line_size() / size_of_type) - 1,
					processer_num -1);
			else
			    fsbe_printf(cx, "(0:%d,0:%d)\n",
                                        count[i] - 1,
                                        processer_num -1);
		    }
		}
	    }
	    free(count);
	}
    }
}
