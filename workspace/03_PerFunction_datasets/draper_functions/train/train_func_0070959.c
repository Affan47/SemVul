gf_node_dirty_parent_graph(GF_Node *node)
{

	if (node->sgprivate->scenegraph->NodeCallback ) {
		node->sgprivate->scenegraph->NodeCallback(node->sgprivate->scenegraph->userpriv, GF_SG_CALLBACK_GRAPH_DIRTY, NULL, NULL);
	}
}
