wbcg_rangesel_possible (WBCGtk const *wbcg)
{
	g_return_val_if_fail (IS_WBC_GTK (wbcg), FALSE);


	if (wbcg->rangesel != NULL)
		return TRUE;


	if (!wbcg_is_editing (wbcg) && !wbcg_entry_has_logical (wbcg))
		return FALSE;

	return gnm_expr_entry_can_rangesel (wbcg_get_entry_logical (wbcg));
}
