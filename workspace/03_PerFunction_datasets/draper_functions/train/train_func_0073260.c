callback_send_a_stream_destroy(void *user, VNodeID node_id, VLayerID stream_id)
{
	VSNodeAudio *node;
	unsigned int i, count;

	node = (VSNodeAudio *)vs_get_node(node_id, V_NT_AUDIO);
	if(node == NULL || stream_id >= node->stream_count || node->streams[stream_id].name[0] == 0)
		return;
	vs_remove_subscriptor(node->streams[stream_id].subscribers);
	node->streams[stream_id].name[0] = 0;
	count =	vs_get_subscript_count(node->head.subscribers);
	for(i = 0; i < count; i++)
	{
		vs_set_subscript_session(node->head.subscribers, i);
		verse_send_a_stream_destroy(node_id, stream_id);
	}
	vs_reset_subscript_session();
}
