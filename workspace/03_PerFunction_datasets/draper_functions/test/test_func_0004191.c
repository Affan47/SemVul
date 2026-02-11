updatescreen(void)
{

	sound_update();


	if (osd_skip_this_frame() == 0)
	{
		profiler_mark(PROFILER_VIDEO);
		draw_screen();
		profiler_mark(PROFILER_END);
	}


	if (handle_user_interface(artwork_get_ui_bitmap()))

		return 1;


	update_video_and_audio();


	if (Machine->drv->video_eof)
	{
		profiler_mark(PROFILER_VIDEO);
		(*Machine->drv->video_eof)();
		profiler_mark(PROFILER_END);
	}

	return 0;
}
