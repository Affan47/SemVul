frame_set_bgcolor(gint32 frame_id, gint32 bgcolor)  {

	if(!engine->active_frame[frame_id]) return;

	frame[frame_id]->bgcolor[0] = (bgcolor >> 16) & 0xff;
	frame[frame_id]->bgcolor[1] = (bgcolor >> 8) & 0xff;
	frame[frame_id]->bgcolor[2] = bgcolor & 0xff;

	if(frame[frame_id]->bgcolor[0] == frame[frame_id]->bgcolor[1]  &&  frame[frame_id]->bgcolor[1] == frame[frame_id]->bgcolor[2])
		frame[frame_id]->gray_bgcolor = TRUE;
	else
		frame[frame_id]->gray_bgcolor = FALSE;
}
