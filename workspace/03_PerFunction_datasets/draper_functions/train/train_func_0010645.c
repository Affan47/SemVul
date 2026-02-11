initBitmaps(char *fname_left, char *fname_middle, char *fname_right, char *fname_dots)
{
	Wingman_status_left.first_frame = bm_load_animation(fname_left, &Wingman_status_left.num_frames);
	if ( Wingman_status_left.first_frame == -1 ) {
		Warning(LOCATION, "Error loading %s\n", fname_left);
	}

	Wingman_status_middle.first_frame = bm_load_animation(fname_middle, &Wingman_status_middle.num_frames);
	if ( Wingman_status_middle.first_frame == -1 ) {
		Warning(LOCATION, "Error loading %s\n", fname_middle);
	}

	Wingman_status_right.first_frame = bm_load_animation(fname_right, &Wingman_status_right.num_frames);
	if ( Wingman_status_right.first_frame == -1 ) {
		Warning(LOCATION, "Error loading %s\n", fname_right);
	}

	Wingman_status_dots.first_frame = bm_load_animation(fname_dots, &Wingman_status_dots.num_frames);
	if ( Wingman_status_dots.first_frame == -1 ) {
		Warning(LOCATION, "Error loading %s\n", fname_dots);
	}
}
