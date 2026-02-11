frame_set_height(gint32 frame_id, gint32 height)  {

	if(!engine->active_frame[frame_id]) return;

	frame[frame_id]->height = height;
}
