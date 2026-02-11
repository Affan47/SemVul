gal_a11y_e_cell_remove_action (GalA11yECell *cell,
                               gint action_index)
{
	GList *list_node;

	g_return_val_if_fail (GAL_A11Y_IS_E_CELL (cell), FALSE);
	list_node = g_list_nth (cell->action_list, action_index);
	if (!list_node)
		return FALSE;
	g_return_val_if_fail (list_node->data != NULL, FALSE);
	_gal_a11y_e_cell_destroy_action_info (list_node->data, NULL);
	cell->action_list = g_list_remove_link (cell->action_list, list_node);

	return TRUE;
}
