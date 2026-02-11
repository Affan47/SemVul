load_wing_icons(char *filename)
{
	int first_frame, num_frames;

	first_frame = bm_load_animation(filename, &num_frames);
	if ( first_frame == -1 ) {
		Error(LOCATION, "Could not load icons from %s\n", filename);
		return;
	}

	Wing_slot_disabled_bitmap = first_frame;
	Wing_slot_empty_bitmap = first_frame + 1;

}
