ui_animate_cb ()
{
	int ret;
	byte *move;
	if (ui_stopped) return TRUE;
	if (!game_animate) return FALSE;
	if (game_animate (&cur_pos, &move) > 0)
	{
		if (game_animation_use_movstack)
			ui_make_human_move (move, NULL);
		else
			board_apply_refresh (move, NULL);
	}
	return TRUE;
}
