do_shorthand_operation__add_padding(const char *filename, FLAC__Metadata_Chain *chain, unsigned length, FLAC__bool *needs_write)
{
	FLAC__StreamMetadata *padding = 0;
	FLAC__Metadata_Iterator *iterator = FLAC__metadata_iterator_new();

	if(0 == iterator)
		die("out of memory allocating iterator");

	FLAC__metadata_iterator_init(iterator, chain);

	while(FLAC__metadata_iterator_next(iterator))
		;

	padding = FLAC__metadata_object_new(FLAC__METADATA_TYPE_PADDING);
	if(0 == padding)
		die("out of memory allocating PADDING block");

	padding->length = length;

	if(!FLAC__metadata_iterator_insert_block_after(iterator, padding)) {
		print_error_with_chain_status(chain, "%s: ERROR: adding new PADDING block to metadata", filename);
		FLAC__metadata_object_delete(padding);
		FLAC__metadata_iterator_delete(iterator);
		return false;
	}

	FLAC__metadata_iterator_delete(iterator);
	*needs_write = true;
	return true;
}
