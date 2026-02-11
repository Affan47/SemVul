convert_to_seek_table_template(const char *requested_seek_points, int num_requested_seek_points, FLAC__StreamMetadata *cuesheet, EncoderSession *e)
{
	const FLAC__bool only_placeholders = e->is_stdout;
	FLAC__bool has_real_points;

	if(num_requested_seek_points == 0 && 0 == cuesheet)
		return true;

	if(num_requested_seek_points < 0) {
#if FLAC__HAS_OGG

		if(e->use_ogg && e->total_samples_to_encode > 0 && e->total_samples_to_encode / e->info.sample_rate / 10 > 230)
			requested_seek_points = "230x;";
		else
#endif
			requested_seek_points = "10s;";
		num_requested_seek_points = 1;
	}

	if(num_requested_seek_points > 0) {
		if(!grabbag__seektable_convert_specification_to_template(requested_seek_points, only_placeholders, e->total_samples_to_encode, e->info.sample_rate, e->seek_table_template, &has_real_points))
			return false;
	}

	if(0 != cuesheet) {
		unsigned i, j;
		const FLAC__StreamMetadata_CueSheet *cs = &cuesheet->data.cue_sheet;
		for(i = 0; i < cs->num_tracks; i++) {
			const FLAC__StreamMetadata_CueSheet_Track *tr = cs->tracks+i;
			for(j = 0; j < tr->num_indices; j++) {
				if(!FLAC__metadata_object_seektable_template_append_point(e->seek_table_template, tr->offset + tr->indices[j].offset))
					return false;
				has_real_points = true;
			}
		}
		if(has_real_points)
			if(!FLAC__metadata_object_seektable_template_sort(e->seek_table_template, true))
				return false;
	}

	if(has_real_points) {
		if(e->is_stdout) {
			flac__utils_printf(stderr, 1, "%s: WARNING, cannot write back seekpoints when encoding to stdout\n", e->inbasefilename);
			if(e->treat_warnings_as_errors)
				return false;
		}
	}

	return true;
}
