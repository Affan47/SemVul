search_ope_init(Module_table *mp, int entry)
{
    Statement *s;
    Quadruple *q;

    for (s = mp->block_head->pre_head->stm_head; s != NULL; s = s->next) {
	if (s->ope == OPE_INIT) {

	    for(q = s->qr_head; q != NULL && q->ope != OPE_ASSIGN; q = q->next);
	    if (q != NULL && q->op[0]->entry == entry) {
		return s;
	    }
	}
    }

    return NULL;
}
