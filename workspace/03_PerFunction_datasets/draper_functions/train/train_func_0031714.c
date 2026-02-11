cs_engine_advance(cs_engine_t *e, double to_frame)
{
	if(to_frame > 0)
	{
		int frames = floor(to_frame) - floor(e->time);
		if(frames > 0)
		{
			while(frames--)
			{
				__run_all(e);
				e->on_frame(e);
			}
		}
	}
	e->time = to_frame;
	if(e->wx || e->wy)
		__wrap_all(e);
	__update_points(e, to_frame - floor(to_frame));
}
