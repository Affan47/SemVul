make_array_region_loop_dim(Module_table *mpt,
                           Array_lmad_region *region_head,
                           Quadruple *quad)
{
    Array_lmad_region *region;
    Array_lmad_dim *array_dim;
    SemTree *loop_start, *end, *loop_end, *loop_step, *var_step;
    SemTree *base, *step, *term;
    int entry;

    entry = quad->op[0]->entry;
    loop_start = make_semtree_operand(mpt, quad->op[1], quad);
    loop_end = make_semtree_operand(mpt, quad->op[2], quad);
    loop_step = make_semtree_operand(mpt, quad->op[3], quad);

    for(region = region_head; region != NULL; region = region->next) {
	if(region->base == NULL) {
	    continue;
	}
	semtree_process(region->base);
	term = search_term_scalar_entry_from_semtree(region->base, entry);
	if(term == NULL) {
	    continue;
	}
	var_step = coefficient_of_term_from_semtree(term, entry);
	step = make_semtree(OPE_MUL, loop_step, var_step);
	base = make_semtree(OPE_SUB, region->base, term);
	semtree_replace_scalar(term, entry, loop_start);
	base = make_semtree(OPE_ADD, base, term);
	region->base = base;
	end = make_semtree(OPE_SUB, loop_end, loop_start);
	end = make_semtree(OPE_MUL, var_step, end);

	semtree_process(region->base);
	semtree_process(step);
	semtree_process(end);

	semtree_destruct(term);
	semtree_destruct(var_step);

	if(region->dim_head == NULL) {
	    region->dim_head = make_array_lmad_dim(step, end, NULL);
	    semtree_destruct(step);
	    semtree_destruct(end);
	}
	else {
	    for(array_dim = region->dim_head;
                array_dim->next_dim != NULL;
                array_dim = array_dim->next_dim) {};
	    array_dim->next_dim = make_array_lmad_dim(step, end, NULL);
	    semtree_destruct(step);
	    semtree_destruct(end);
	}
    }

    semtree_destruct(loop_start);
    semtree_destruct(loop_end);
    semtree_destruct(loop_step);
}
