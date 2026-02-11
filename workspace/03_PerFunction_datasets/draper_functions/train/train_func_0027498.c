set_galms_all_mpt(Module_table *module_head, Galms *galms,
		  IntSet *func_local_array, IntSet *subr_local_array,
		  real **funcgain, real **subgain,
		  IntSet funcset, IntSet subrset,
		  const int level, int *count)
{
    Module_table *mpt = NULL;
    real **target_gain;

    for (mpt = module_head; mpt != NULL; mpt = mpt->next) {
        if ((mpt->kind == MODULE_FUNC && in_IntSet(funcset, mpt->entry))
            || (mpt->kind == MODULE_SUB && in_IntSet(subrset, mpt->entry))) {
            IntSet module_local_array = (mpt->kind == MODULE_FUNC)
                ? func_local_array[mpt->entry] : subr_local_array[mpt->entry];
            target_gain = (mpt->kind == MODULE_FUNC)
                ? funcgain : subgain;

	    if(localize_with_pa)
		set_galms_all_mpt_body_pa(mpt, galms, module_local_array, target_gain, level, count);
	    else
		set_galms_all_mpt_body(mpt, galms, module_local_array, target_gain, level, count);

        }
    }

}
