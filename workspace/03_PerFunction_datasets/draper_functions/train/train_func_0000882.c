message_calc_anim_start_frame(int time, generic_anim *ani, int reverse)
{
	float	wave_time, anim_time;
	int	start_frame;

	start_frame=0;


	if ( time <= 0 ) {
		return;
	}


	wave_time = time/1000.0f;
	anim_time = ani->total_time;


	if ( wave_time >= (anim_time) ) {
		return;
	}

	float fps = ani->num_frames / ani->total_time;
	if ( reverse ) {
		start_frame = (ani->num_frames-1) - fl2i(fps * wave_time + 0.5f);
	} else {
		int num_frames_extra;
		num_frames_extra = fl2i(fps * (anim_time - wave_time) + 0.5f);
		if ( num_frames_extra > 0 ) {
			start_frame=rand()%num_frames_extra;
		}
	}

	if ( start_frame < 0 ) {
		Int3();
		start_frame=0;
	}

	ani->current_frame = start_frame;
	ani->anim_time = start_frame / fps;
}
