get_current_fps(void)
{
	static float time_since_last_fps_update = 10;
	static int frames_counted = 0;
	static int current_fps = 0;

	time_since_last_fps_update += Frame_Time();
	frames_counted++;
	if (frames_counted > 50) {
		current_fps = frames_counted / time_since_last_fps_update;
		time_since_last_fps_update = 0;
		frames_counted = 0;
	}
	return current_fps;
}
