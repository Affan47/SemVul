VID_GetModeInfo ( int *width, int *height, int mode)
{
	vidmode_t *vm;

	if ( mode < -1 )
	{
		return false;
	}

	if ( mode >= s_numVidModes )
	{
		return false;
	}

	if ( mode == -1 )
	{
		*width = vid_width->value;
		*height = vid_height->value;
		return true;
	}

	vm = &vid_modes[mode];

	*width = vm->width;
	*height = vm->height;

	return true;
}
