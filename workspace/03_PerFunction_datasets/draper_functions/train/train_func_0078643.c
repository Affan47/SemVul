player_clear_speed_matching()
{
	if ( !Player ) {
		Int3();
		return;
	}

	Player->flags &= ~PLAYER_FLAGS_MATCH_TARGET;
	Player->flags &= ~PLAYER_FLAGS_AUTO_MATCH_SPEED;
}
