distribute_cond_expr_statements(Statement *stm_head)
{
    Statement *spt;

    for (spt = stm_head; spt != NULL; spt = spt->next) {
	if (conditional_jump_operator_p(spt->ope)) {
	    distribute_cond_expr_quadruples (spt->qr_head);
	}
    }
}
