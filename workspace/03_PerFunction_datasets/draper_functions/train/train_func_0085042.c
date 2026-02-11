lad_sm_check_def_lm(Block *block, Array_table *ldm)
{
    UDlist *dul, *deflist;
    Array_table *def_lm;

    deflist = make_deflist(block);

    for (dul = deflist; dul != NULL; dul = dul->next) {
	def_lm = lad_sm_change_csm_to_lm(block->module, dul->aryno);
	if (ldm->entry == def_lm->entry) {
	    return TRUE;
	}
    }
    return FALSE;
}
