do_cmd_wiz_bamf(void)
{
	s16b x, y;


	if (!target_okay()) return;


	target_get(&x, &y);
	teleport_player_to(y, x);
}
