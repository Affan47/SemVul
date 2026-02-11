wbcg_sheet_order_changed (WBCGtk *wbcg)
{
	GSList *l, *scgs = get_all_scgs (wbcg);
	int i;


	scgs = g_slist_sort (scgs, by_sheet_index);

	for (i = 0, l = scgs; l; l = l->next, i++) {
		SheetControlGUI *scg = l->data;
		gtk_notebook_reorder_child (wbcg->snotebook,
					    GTK_WIDGET (scg->grid),
					    i);
		gnm_notebook_move_tab (wbcg->bnotebook,
				       GTK_WIDGET (scg->label),
				       i);
	}

	g_slist_free (scgs);
}
