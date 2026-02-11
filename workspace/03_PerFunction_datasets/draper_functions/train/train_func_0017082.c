pi_set_description(FLAC__StreamMetadata *block, const FLAC__byte *s)
{
	if(block->data.picture.description) {
		block->length -= strlen((const char *)block->data.picture.description);
		free(block->data.picture.description);
	}
	block->data.picture.description = (FLAC__byte*)strdup((const char *)s);
	FLAC__ASSERT(block->data.picture.description);
	block->length += strlen((const char *)block->data.picture.description);
}
