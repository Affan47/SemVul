FitLinkDataStructure(Module_table *target,
		     Block        *block)
{
    Block        *bpt = NULL;
    Pe_statement *pe  = NULL;
    Statement    *stm = NULL;
    Quadruple    *qr  = NULL;

    for(bpt = block; bpt != NULL; bpt = bpt->next){
	bpt->module = target;
	for(pe = bpt->pre_head; pe != NULL; pe = pe->next){
	    pe->block = bpt;
	    for(stm = pe->stm_head; stm != NULL; stm = stm->next){
		stm->pe_stm = pe;
		for(qr = stm->qr_head; qr != NULL; qr = qr->next){
		    qr->stm = stm;
		}
	    }
	}
	for(pe = bpt->post_head; pe != NULL; pe = pe->next){
	    pe->block = bpt;
	    for(stm = pe->stm_head; stm != NULL; stm = stm->next){
		stm->pe_stm = pe;
		for(qr = stm->qr_head; qr != NULL; qr = qr->next){
		    qr->stm = stm;
		}
	    }
	}
	if(bpt->inner != NULL){
	    FitLinkDataStructure(target, bpt->inner);
	    fit_link_block_outer_and_inner(bpt, bpt->inner);
	}
    }
}
