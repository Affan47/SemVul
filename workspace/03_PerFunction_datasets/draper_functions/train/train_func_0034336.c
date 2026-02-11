sol_pma_free(struct isl_sol_pma *sol_pma)
{
	if (!sol_pma)
		return;
	if (sol_pma->sol.context)
		sol_pma->sol.context->op->free(sol_pma->sol.context);
	isl_pw_multi_aff_free(sol_pma->pma);
	isl_set_free(sol_pma->empty);
	free(sol_pma);
}
