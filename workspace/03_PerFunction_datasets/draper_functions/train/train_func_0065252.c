make_load_range_use_upper(StripMiningInnerLoop *smil,
			  Array_def_use_table_semnode *load)
{
    SemTree *upper;
    Var_table *max_access_var;
    Array_table *lm;

    lm = lad_sm_change_csm_to_lm(smil->sm->module, load->entry);
    max_access_var = lad_sm_get_upper_strip_mining_cmp(smil->sm->cmp_head,
						       lm->entry);
    upper = make_semtree_scalar(smil->sm->module, max_access_var);


    if (upper == NULL) {
	fatal("can't make load range use upper\n");
	abort();
    }

    return upper;
}
