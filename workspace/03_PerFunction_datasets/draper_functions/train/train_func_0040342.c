wbcg_set_entry (WBCGtk *wbcg, GnmExprEntry *entry)
{
	g_return_if_fail (IS_WBC_GTK (wbcg));

	if (wbcg->edit_line.temp_entry != entry) {
		scg_rangesel_stop (wbcg_cur_scg (wbcg), FALSE);
		wbcg->edit_line.temp_entry = entry;
	}
}
