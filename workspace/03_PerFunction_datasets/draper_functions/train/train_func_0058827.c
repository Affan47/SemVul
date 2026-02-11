search_def_var_inner(Module_table *mpt,
			  Block        *do_block,
			  Block        *sum_block,
			  Block        *body,
			  int          div_num)
{
    if (body != NULL) {
        search_def_var_pe(mpt, do_block, sum_block, body->pre_head, div_num);
        if (body->inner != NULL)
	  search_def_var(mpt, do_block, sum_block,
			 body->inner, div_num);
    }
}
