set_frame_delay(int frameno, float delay)
{
	CL_Sprite_Generic::SpriteFrame *frame = impl->get_frame(frameno);
	if(frame)
		frame->delay = delay;
}
