tree_table_adapter_source_model_node_inserted_cb (ETreeModel *etm,
                                                  ETreePath parent,
                                                  ETreePath child,
                                                  ETreeTableAdapter *etta)
{
	if (e_tree_model_node_is_root (etm, child))
		generate_tree (etta, child);
	else
		insert_node (etta, parent, child);

	e_table_model_changed (E_TABLE_MODEL (etta));
}
