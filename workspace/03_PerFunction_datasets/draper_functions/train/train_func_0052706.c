callback_send_c_curve_destroy(void *user, VNodeID node_id, VLayerID curve_id)
{
	VSNodeCurve *node;
	unsigned int i, count;
	node = (VSNodeCurve *)vs_get_node(node_id, V_NT_CURVE);
	if(node == NULL || node->curve_count >= curve_id || node->curves[curve_id].name[0] == 0)
		return;
	vs_remove_subscriptor(node->curves[curve_id].subscribers);
	node->curves[curve_id].name[0] = 0;
	free(node->curves[curve_id].keys);
	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_c_curve_destroy(node_id, curve_id);
	}
	vs_reset_subscript_session();
}
