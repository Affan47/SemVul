comm_pack_collected_extras( unsigned char *msg, int *pos )
{
	int i, j;

	for ( i = 0; i < cur_game->paddle_count; i++ ) {
		msg[(*pos)++] = cur_game->mod.collected_extra_count[i];
		for ( j = 0; j < cur_game->mod.collected_extra_count[i]; j++ )
			msg[(*pos)++] = (unsigned char)cur_game->mod.collected_extras[i][j];
	}
}
