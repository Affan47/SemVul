set_scaling(int scale)
{
	if (scale==1) {
		screen_width=800;
		screen_height=512;
		scale_up=1;
		dirty_block_shift=5;
		screen_pitch=screen_width;
	} else {
		screen_width=400;
		screen_height=256;
		scale_up=0;
		dirty_block_shift=4;
		screen_pitch=screen_width;
	}
}
