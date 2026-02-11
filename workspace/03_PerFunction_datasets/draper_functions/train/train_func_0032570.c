FLAC__metadata_iterator_delete_block(FLAC__Metadata_Iterator *iterator, FLAC__bool replace_with_padding)
{
	FLAC__Metadata_Node *save;

	FLAC__ASSERT(0 != iterator);
	FLAC__ASSERT(0 != iterator->current);

	if(0 == iterator->current->prev) {
		FLAC__ASSERT(iterator->current->data->type == FLAC__METADATA_TYPE_STREAMINFO);
		return false;
	}

	save = iterator->current->prev;

	if(replace_with_padding) {
		FLAC__metadata_object_delete_data(iterator->current->data);
		iterator->current->data->type = FLAC__METADATA_TYPE_PADDING;
	}
	else {
		chain_delete_node_(iterator->chain, iterator->current);
	}

	iterator->current = save;
	return true;
}
