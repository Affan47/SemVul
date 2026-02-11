del(tree **ppr_r, int *pi_balance, tree **ppr_q,
    void (*pfv_uar)(tree_t), int *pi_uar_called)
{
	ENTER("del")

	if ((*ppr_r)->right != NULL) {
		del(&(*ppr_r)->right, pi_balance, ppr_q,
		    pfv_uar, pi_uar_called);
		if (*pi_balance)
			bal_R(ppr_r, pi_balance);
	} else {
		if (pfv_uar)
			(*pfv_uar)((*ppr_q)->data);
		*pi_uar_called = TRUE;
		(*ppr_q)->data = (*ppr_r)->data;
		*ppr_q = *ppr_r;
		*ppr_r = (*ppr_r)->left;
		*pi_balance = TRUE;
	}

	RETV
}
