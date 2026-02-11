FLAC__metadata_get_streaminfo(const char *filename, FLAC__StreamMetadata *streaminfo)
{
	FLAC__StreamMetadata *object;

	FLAC__ASSERT(0 != filename);
	FLAC__ASSERT(0 != streaminfo);

	object = get_one_metadata_block_(filename, FLAC__METADATA_TYPE_STREAMINFO);

	if (object) {

		*streaminfo = *object;
		FLAC__metadata_object_delete(object);
		return true;
	}
	else {
		return false;
	}
}
