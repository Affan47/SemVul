render(float frametime)
{
	if ( timestamp_elapsed(Hud_text_flash_timer) || !Hud_text_flash) {
		return;
	}

	if(strlen(Hud_text_flash) <= 0) {
		return;
	}

	int w, h;


	gr_get_string_size(&w, &h, Hud_text_flash);


	if(maybeTextFlash()){
		setGaugeColor(HUD_C_DIM);


		renderRect( (int)( (float)position[0] - (float)w / 2.0f - 1.0f), (int)((float)position[1] - 1.0f), w + 2, h + 1);
	}


	setGaugeColor(HUD_C_BRIGHT);
	renderString(fl2i((float)position[0] - ((float)w / 2.0f)), position[1], Hud_text_flash);
}
