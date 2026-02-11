FLAC__metadata_object_cuesheet_track_resize_indices(FLAC__StreamMetadata *object, unsigned track_num, unsigned new_num_indices)
{
	FLAC__StreamMetadata_CueSheet_Track *track;
	FLAC__ASSERT(0 != object);
	FLAC__ASSERT(object->type == FLAC__METADATA_TYPE_CUESHEET);
	FLAC__ASSERT(track_num < object->data.cue_sheet.num_tracks);

	track = &object->data.cue_sheet.tracks[track_num];

	if(0 == track->indices) {
		FLAC__ASSERT(track->num_indices == 0);
		if(0 == new_num_indices)
			return true;
		else if(0 == (track->indices = cuesheet_track_index_array_new_(new_num_indices)))
			return false;
	}
	else {
		const size_t old_size = track->num_indices * sizeof(FLAC__StreamMetadata_CueSheet_Index);
		const size_t new_size = new_num_indices * sizeof(FLAC__StreamMetadata_CueSheet_Index);


		if(new_num_indices > UINT32_MAX / sizeof(FLAC__StreamMetadata_CueSheet_Index))
			return false;

		FLAC__ASSERT(track->num_indices > 0);

		if(new_size == 0) {
			free(track->indices);
			track->indices = 0;
		}
		else if(0 == (track->indices = realloc(track->indices, new_size)))
			return false;


		if(new_size > old_size)
			memset(track->indices + track->num_indices, 0, new_size - old_size);
	}

	track->num_indices = new_num_indices;

	cuesheet_calculate_length_(object);
	return true;
}
