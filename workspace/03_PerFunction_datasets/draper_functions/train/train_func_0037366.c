initBitmaps(char *fname_first, char *fname_entry, char *fname_last)
{
	_background_first.first_frame = bm_load_animation(fname_first, &_background_first.num_frames);
	if(_background_first.first_frame < 0) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", fname_first);
	}

	_background_entry.first_frame = bm_load_animation(fname_entry, &_background_entry.num_frames);
	if(_background_entry.first_frame < 0) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", fname_entry);
	}

	_background_last.first_frame = bm_load_animation(fname_last, &_background_last.num_frames);
	if(_background_last.first_frame < 0) {
		Warning(LOCATION,"Cannot load hud ani: %s\n", fname_last);
	}
}
