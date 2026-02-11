ui_make_human_move (byte *move, int *rmove)
{
	board_apply_refresh (move, rmove);
	if (!move) return;
	if (move_fout)
	{
		fprintf (move_fout, "TAKE_MOVE ");
		move_fwrite (move, move_fout);
		if (opt_logfile)
			move_fwrite (move, opt_logfile);
	}
	if (!game_single_player)
	{
		cur_pos.player = (cur_pos.player == WHITE ? BLACK : WHITE);
	}
	cur_pos.num_moves ++;
	ui_check_who_won ();
	sb_update ();
	ui_send_make_move ();
}
