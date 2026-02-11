render(float frametime)
{
	if (Player_ship->flags2 & SF2_PRIMITIVE_SENSORS)
		return;

	int frame_offset;

	if ( Players[Player_num].flags & PLAYER_FLAGS_AUTO_MATCH_SPEED ) {
		frame_offset = 3;
	} else {
		frame_offset = 2;
	}

	setGaugeColor();

	renderBitmap(Toggle_frame.first_frame+frame_offset, position[0], position[1]);


	if (frame_offset == 3) {


		if ( Use_on_color ) {
			gr_set_color_fast(&On_color);
		}
	} else if ( Use_off_color ) {
		gr_set_color_fast(&Off_color);
	}
	renderString(position[0] + Auto_text_offsets[0], position[1] + Auto_text_offsets[1], XSTR("auto", 1463));
	renderString(position[0] + Speed_text_offsets[0], position[1] + Speed_text_offsets[1], XSTR("speed", 1464));
}
