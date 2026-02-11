semtree_stm(Module_table *mpt, Statement *stm_head)
{
    int i;
    SemanticNode *node;
    Statement *stm;
    Quadruple *quad, *qrp;

    stm = stm_head;
    while(stm != NULL){
	quad = stm->qr_head;
	if(stm->ope == OPE_DO){
	    for(i = 0; i < 3; i++){
		qrp = quad;
		while(qrp != NULL && qrp->ope != OPE_DO)
		    qrp = qrp->next;
		node = ConstructSemTree(qrp, qrp->op[i+1]);
		stm->sym_code[i] = node;
	    }
	} else {
	    node = semtree_quad(mpt, quad);
	    stm->sym_code[0] = node;
	}
	stm = stm->next;
    }
}
