src_close(src_t *src)
{
	int r;

	if(src->captured_frames)
	{
		double seconds =
		   (src->tv_last.tv_sec  + src->tv_last.tv_usec  / 1000000.0) -
		   (src->tv_first.tv_sec + src->tv_first.tv_usec / 1000000.0);


		if(src->captured_frames == 1)
		{
			MSG("Captured frame in %0.2f seconds.", seconds);
		}
		else if(src->captured_frames < 3)
		{
			MSG("Captured %i frames in %0.2f seconds.",
			    src->captured_frames, seconds);
		}
		else
		{
			MSG("Captured %i frames in %0.2f seconds. (%i fps)",
			    src->captured_frames, seconds,
			    (int) (src->captured_frames / seconds));
		}
	}

	r = src_mod[src->type]->close(src);

	if(src->source) free(src->source);

	return(r);
}
