rewrite_whole_file_(FLAC__Metadata_SimpleIterator *iterator, FLAC__StreamMetadata *block, FLAC__bool append)
{
	FILE *tempfile = NULL;
	char *tempfilename = NULL;
	int fixup_is_last_code = 0;
	FLAC__off_t fixup_is_last_flag_offset = -1;

	FLAC__ASSERT(0 != block || append == false);

	if(iterator->is_last) {
		if(append) {
			fixup_is_last_code = 1;
			fixup_is_last_flag_offset = iterator->offset[iterator->depth];
		}
		else if(0 == block) {
			simple_iterator_push_(iterator);
			if(!FLAC__metadata_simple_iterator_prev(iterator)) {
				(void)simple_iterator_pop_(iterator);
				return false;
			}
			fixup_is_last_code = -1;
			fixup_is_last_flag_offset = iterator->offset[iterator->depth];
			if(!simple_iterator_pop_(iterator))
				return false;
		}
	}

	if(!simple_iterator_copy_file_prefix_(iterator, &tempfile, &tempfilename, append))
		return false;

	if(0 != block) {
		if(!write_metadata_block_header_(tempfile, &iterator->status, block)) {
			cleanup_tempfile_(&tempfile, &tempfilename);
			return false;
		}

		if(!write_metadata_block_data_(tempfile, &iterator->status, block)) {
			cleanup_tempfile_(&tempfile, &tempfilename);
			return false;
		}
	}

	if(!simple_iterator_copy_file_postfix_(iterator, &tempfile, &tempfilename, fixup_is_last_code, fixup_is_last_flag_offset, block==0))
		return false;

	if(append)
		return FLAC__metadata_simple_iterator_next(iterator);

	return true;
}
