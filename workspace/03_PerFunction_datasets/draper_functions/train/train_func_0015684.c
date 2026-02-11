ect_kill_view (ECellView *ecv)
{
	ECellTreeView *tree_view = (ECellTreeView *) ecv;

	if (tree_view->cell_view.kill_view_cb)
	    (tree_view->cell_view.kill_view_cb)(ecv, tree_view->cell_view.kill_view_cb_data);

	if (tree_view->cell_view.kill_view_cb_data)
	    g_list_free (tree_view->cell_view.kill_view_cb_data);


	e_cell_kill_view (tree_view->subcell_view);

	g_free (tree_view);
}
