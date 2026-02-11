multi_pinfo_popup_close()
{
	int idx;


	if(Multi_pinfo_bitmap != -1){
		bm_release(Multi_pinfo_bitmap);
	}


	if(Multi_pinfo_screen_save >= 0){
		gr_free_screen(Multi_pinfo_screen_save);
	}


	if(Mp_pilot.bitmap != -1){
		bm_release(Mp_pilot.bitmap);
	}
	if(Mp_squad.bitmap != -1){
		bm_release(Mp_squad.bitmap);
	}


	for(idx=0; idx<MULTI_PINFO_NUM_STATS_LABELS; idx++){
		if(Multi_pinfo_stats_labels[idx] != NULL){
			vm_free(Multi_pinfo_stats_labels[idx]);
			Multi_pinfo_stats_labels[idx] = NULL;
		}
	}


	Multi_pinfo_popup_player = NULL;


	Multi_pinfo_popup_running = 0;


	Multi_pinfo_window.destroy();


	Detail.hardware_textures = Multi_pinfo_hardware_texture_backup;
}
