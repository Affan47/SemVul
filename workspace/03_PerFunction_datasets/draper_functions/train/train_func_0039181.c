FLAC__metadata_object_seektable_template_append_spaced_points(FLAC__StreamMetadata *object, unsigned num, FLAC__uint64 total_samples)
{
	FLAC__ASSERT(0 != object);
	FLAC__ASSERT(object->type == FLAC__METADATA_TYPE_SEEKTABLE);
	FLAC__ASSERT(total_samples > 0);

	if(num > 0 && total_samples > 0) {
		FLAC__StreamMetadata_SeekTable *seek_table = &object->data.seek_table;
		unsigned i, j;

		i = seek_table->num_points;

		if(!FLAC__metadata_object_seektable_resize_points(object, seek_table->num_points + num))
			return false;

		for(j = 0; j < num; i++, j++) {
			seek_table->points[i].sample_number = total_samples * (FLAC__uint64)j / (FLAC__uint64)num;
			seek_table->points[i].stream_offset = 0;
			seek_table->points[i].frame_samples = 0;
		}
	}

	return true;
}
