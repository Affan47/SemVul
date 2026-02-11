FLAC__metadata_object_seektable_template_sort(FLAC__StreamMetadata *object, FLAC__bool compact)
{
	unsigned unique;

	FLAC__ASSERT(0 != object);
	FLAC__ASSERT(object->type == FLAC__METADATA_TYPE_SEEKTABLE);

	unique = FLAC__format_seektable_sort(&object->data.seek_table);

	return !compact || FLAC__metadata_object_seektable_resize_points(object, unique);
}
