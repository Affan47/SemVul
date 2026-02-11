multi_pxo_notify_blit()
{
	int w;


	if(Multi_pxo_notify_stamp == -1){
		return;
	}


	if(timestamp_elapsed(Multi_pxo_notify_stamp)){
		Multi_pxo_notify_stamp = -1;
	}


	gr_set_color_fast(&Color_bright);
	gr_get_string_size(&w,NULL,Multi_pxo_notify_text);
	gr_string((gr_screen.max_w - w)/2,MULTI_PXO_NOTIFY_Y,Multi_pxo_notify_text);
}
