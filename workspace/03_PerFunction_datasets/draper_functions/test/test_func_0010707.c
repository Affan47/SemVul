callback_send_o_method_group_unsubscribe(void *user, VNodeID node_id, uint16 group_id)
{
	VSNodeObject *node;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL || vs_get_node(node_id, V_NT_OBJECT) == NULL)
		return;
	if(group_id < node->group_count && node->groups[group_id].name[0] != 0)
		vs_remove_subscriptor(node->groups[group_id].subscribers);
}
