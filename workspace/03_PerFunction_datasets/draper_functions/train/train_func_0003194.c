players_set_current( int current )
{
    if ( current < 0 || current >= player_count ) return 0;
    current_player = current;
	return &players[current_player];
}
