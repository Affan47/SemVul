FLAC__metadata_iterator_insert_block_after(FLAC__Metadata_Iterator *iterator, FLAC__StreamMetadata *block)
{
	FLAC__Metadata_Node *node;

	FLAC__ASSERT(0 != iterator);
	FLAC__ASSERT(0 != iterator->current);
	FLAC__ASSERT(0 != block);

	if(block->type == FLAC__METADATA_TYPE_STREAMINFO)
		return false;

	if(0 == (node = node_new_()))
		return false;

	node->data = block;
	iterator_insert_node_after_(iterator, node);
	iterator->current = node;
	return true;
}
