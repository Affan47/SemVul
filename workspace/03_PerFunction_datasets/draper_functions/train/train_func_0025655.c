multi_ingame_load_icons()
{
	int first_frame, num_frames, idx, s_idx;


	for(idx=0;idx<MULTI_INGAME_MAX_SHIP_ICONS;idx++){
		Multi_ingame_ship_icon[idx].ship_class = -1;
		for(s_idx=0;s_idx<NUM_ICON_FRAMES;s_idx++){
			Multi_ingame_ship_icon[idx].bmaps[s_idx] = -1;
		}
	}
	Multi_ingame_num_ship_icons = 0;


	for(idx=0;idx<Num_ship_classes;idx++){

		if((Ship_info[idx].icon_filename[0] != '\0') && (Multi_ingame_num_ship_icons < MULTI_INGAME_MAX_SHIP_ICONS)){

			Multi_ingame_ship_icon[Multi_ingame_num_ship_icons].ship_class = idx;


			first_frame = bm_load_animation(Ship_info[idx].icon_filename, &num_frames);
			if ( first_frame == -1 ) {
				Int3();
			}
			for ( s_idx = 0; s_idx < num_frames; s_idx++ ) {
				Multi_ingame_ship_icon[Multi_ingame_num_ship_icons].bmaps[s_idx] = first_frame+s_idx;
			}

			Multi_ingame_num_ship_icons++;
		}
	}
}
