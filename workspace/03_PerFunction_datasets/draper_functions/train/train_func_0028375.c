xml_print_tree_internal(GNode *node, gpointer data){
	NODE_DATA *node_data;

	node_data = (NODE_DATA *)(node->data);

	if(node_data->name){
		print_indent(node_data->depth);
		printf("%s", node_data->name);
		if(node_data->attr != NULL){
			GList *list;
			NODE_ATTR *attr;
			list = g_list_first(node_data->attr);
			while(list){
				attr = (NODE_ATTR *)(list->data);
				g_print(" %s=%s", attr->name, attr->value);
				list = g_list_next(list);
			}
		}
		g_print("\n");

		if(G_NODE_IS_LEAF(node)){
			print_indent2(node_data->depth);
			if(node_data->content != NULL){
				printf(">%s<\n", node_data->content);
			} else {
				printf("NULL\n");
			}
		} else {
			g_node_children_foreach(node, G_TRAVERSE_ALL, (GNodeForeachFunc)xml_print_tree_internal, (gpointer)NULL);
		}
	} else {
		g_node_children_foreach(node, G_TRAVERSE_ALL, (GNodeForeachFunc)xml_print_tree_internal, (gpointer)NULL);
	}
}
