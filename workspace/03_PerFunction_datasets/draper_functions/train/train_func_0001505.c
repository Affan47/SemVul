shockwave_load(char *s_name, bool shock_3D)
{
	size_t i;
	int s_index = -1;
	shockwave_info *si = NULL;

	Assert( s_name );


	if ( !VALID_FNAME(s_name) )
		return -1;

	for (i = 0; i < Shockwave_info.size(); i++) {
		if ( !stricmp(Shockwave_info[i].filename, s_name) ) {
			s_index = i;
			break;
		}
	}

	if (s_index < 0) {
		shockwave_info si_tmp;

		strcpy_s(si_tmp.filename, s_name);

		Shockwave_info.push_back( si_tmp );
		s_index = (int)(Shockwave_info.size() - 1);
	}

	Assert( s_index >= 0 );
	si = &Shockwave_info[s_index];


	if ( (si->bitmap_id >= 0) || (si->model_id >= 0) )
		return s_index;

	if (shock_3D) {
		si->model_id = model_load( si->filename, 0, NULL );

		if ( si->model_id < 0 ) {
			Shockwave_info.pop_back();
			return -1;
		}
	} else {
		si->bitmap_id = bm_load_animation( si->filename, &si->num_frames, &si->fps, NULL, 1 );

		if ( si->bitmap_id < 0 ) {
			Shockwave_info.pop_back();
			return -1;
		}
	}

	return s_index;
}
