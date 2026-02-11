frame_move_resize(
	FvwmWindow *fw, frame_move_resize_args mr_args)
{
	mr_args_internal *mra;
	Bool is_grabbed = False;
	int i;

	mra = (mr_args_internal *)mr_args;


	if (mra->anim_steps > 1)
	{
		is_grabbed = GrabEm(None, GRAB_FREEZE_CURSOR);
	}

	for (i = 1; i <= mra->anim_steps; i++, frame_next_move_resize_args(mra))
	{
		mra->current_step = i;
		frame_move_resize_step(fw, mra);
	}
	if (is_grabbed == True)
	{
		UngrabEm(GRAB_FREEZE_CURSOR);
	}

	return;
}
