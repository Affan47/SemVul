key_left_released(Game * game)
{
	if (!right_ispressed) {
		game->keyboard_move = 0;
	}
	left_ispressed = FALSE;
}
