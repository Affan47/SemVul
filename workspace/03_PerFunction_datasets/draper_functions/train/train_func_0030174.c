construct_reference_def(Block* bptr, IntSet* prev_def_set,
			int vpe_cnt, int var_num)
{
    int    i;
    int**  def_count;
    Pe_statement* tmp_stm;

    if ((def_count = (int**)malloc(vpe_cnt * sizeof(int*))) == NULL) {
	fatal("No room for memory allocation.");
    }
    for (i = 0; i < vpe_cnt; i++) {
	if ((def_count[i] = (int*)calloc(var_num, sizeof(int))) == NULL) {
	    fatal("No room for memory allocation.");
	}
    }

    for (i = 0; i < bptr->ncfpre; i++) {
	Pe_statement*  prev_stm;

	if (bptr->cfpre[i] != NULL) {
	    for (prev_stm = bptr->cfpre[i]->pre_head;
		 prev_stm != NULL;
		 prev_stm = prev_stm->next) {
		int j;

		for (j = 0; j < var_num; j++) {
		    if (in_IntSet(prev_stm->propagated_def, j)) {
			def_count[prev_stm->vpe_no][j]++;
		    }
		}
	    }
	}
    }
    for (tmp_stm = bptr->pre_head;
	 tmp_stm != NULL;
	 tmp_stm = tmp_stm->next) {
	for (i = 0; i < var_num; i++) {
	    if (def_count[tmp_stm->vpe_no][i] > 0
		&& in_IntSet(tmp_stm->exposed_use, i)) {
		def_count[tmp_stm->vpe_no][i]++;
	    }
	}
    }

    for (i = 0; i < var_num; i++) {
	int  j;
	int  max_count = 0;
	int  max_count_pe = 0;

	for (j = 0; j < vpe_cnt; j++) {
	    if (def_count[j][i] > max_count) {
		max_count = def_count[j][i];
		max_count_pe = j;
	    }
	}
	if (max_count > 0) {
	    add1_IntSet(prev_def_set[max_count_pe], i);
	}
    }
}
