callback_send_a_block_set(void *user, VNodeID node_id, VLayerID buffer_id, uint32 block_index,
				      VNABlockType type, const VNABlock *data)
{
	static const size_t	blocksize[] = {
		VN_A_BLOCK_SIZE_INT8   * sizeof (int8),
		VN_A_BLOCK_SIZE_INT16  * sizeof (int16),
		VN_A_BLOCK_SIZE_INT24  * 3 * sizeof (int8),
		VN_A_BLOCK_SIZE_INT32  * sizeof (int32),
		VN_A_BLOCK_SIZE_REAL32 * sizeof (real32),
		VN_A_BLOCK_SIZE_REAL64 * sizeof (real64)
	};
	VSNodeAudio *node;
	unsigned int i, count;

	if(type > VN_A_BLOCK_REAL64)
		return;

	node = (VSNodeAudio *)vs_get_node(node_id, V_NT_AUDIO);
	if(node == NULL)
		return;
	if(node->buffers[buffer_id].name[0] == 0)
		return;
	if(type != node->buffers[buffer_id].type)
		return;
	if(block_index > node->buffers[buffer_id].length)
	{
		node->buffers[buffer_id].data = realloc(node->buffers[buffer_id].data,
						      (sizeof *node->buffers[buffer_id].data) * (block_index + 64));
		for(i = node->buffers[buffer_id].length; i < block_index + 64; i++)
			node->buffers[buffer_id].data[i] = NULL;
		node->buffers[buffer_id].length = block_index + 64;
	}

	if(node->buffers[buffer_id].data[block_index] == NULL)
		node->buffers[buffer_id].data[block_index] = malloc(blocksize[type]);
	if(node->buffers[buffer_id].data[block_index] != NULL)
	{
		memcpy(node->buffers[buffer_id].data[block_index], data, blocksize[type]);
		count =	vs_get_subscript_count(node->buffers[buffer_id].subscribers);
		for(i = 0; i < count; i++)
		{
			vs_set_subscript_session(node->buffers[buffer_id].subscribers, i);
			verse_send_a_block_set(node_id, buffer_id, block_index, type, data);
		}
		vs_reset_subscript_session();
	}
}
