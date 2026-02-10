lad_sm_search_last_mod_use_block(StripMining *sm,
				 Array_table *ldm,
				 int work)
{
    List *li;
    StripMiningInnerLoop *smil;
    Block *block, *last;
    Array_def_use_table_semnode *mod_use, *aduts;
    int mod_use_entry;
    int flag;

    last = NULL;
    mod_use = NULL;

    for (li = sm->loops; li != NULL; li = li->next) {
	smil = SMIL(li->data);
	block = smil->block;
	if (work == 2) {
	    mod_use = (Array_def_use_table_semnode *)get_array_mayuse(block);
	} else if (work == 1) {
	    mod_use = (Array_def_use_table_semnode *)get_array_maymod(block);
	}
	mod_use = copy_array_def_use_table_semnode(mod_use);
	for (aduts = mod_use; aduts != NULL; aduts = aduts->next) {
	    flag = lad_sm_check_entry_strip_mining_cmp(sm->cmp_head,
						       aduts->entry);
	    if (flag == 0) {
		mod_use_entry =
		    lad_sm_get_csm_ldm_entry_strip_mining_cmp(sm->cmp_head,
							      aduts->entry);
		if (mod_use_entry == ldm->entry) {
		    last = block;
		}

	    }
	}

    }
    return last;
}
