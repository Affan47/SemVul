callback_send_o_transform_scale_real32(void *user, VNodeID node_id, real32 scale_x, real32 scale_y, real32 scale_z)
{
	VSNodeObject *node;
	unsigned int i, count;
	node = (VSNodeObject *)vs_get_node(node_id, V_NT_OBJECT);
	if(node == NULL)
		return;
	node->transform.scale[0] = scale_x;
	node->transform.scale[1] = scale_y;
	node->transform.scale[2] = scale_z;
	count =	vs_get_subscript_count(node->trans_sub64);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->trans_sub64, i);
		verse_send_o_transform_scale_real64(node_id, scale_x, scale_y, scale_z);
	}
	count =	vs_get_subscript_count(node->trans_sub32);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->trans_sub32, i);
		verse_send_o_transform_scale_real32(node_id, scale_x, scale_y, scale_z);
	}
	vs_reset_subscript_session();
}
