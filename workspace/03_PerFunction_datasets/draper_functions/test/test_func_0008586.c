server_game_add( ServerChannel *channel, ServerGameCtx *ctx )
{
	ServerGame *game = salloc( 1, sizeof( ServerGame ) );


	game->state = SERVER_AWAIT_ACCEPT;
	game->id = global_id++;
	game->channel = channel;
	game->set = find_levelset( ctx->name );
	if ( game->set == 0 ) {

		sprintf( errbuf, "game_create_failed: no levelset '%s' found\n", ctx->name );
		send_info( ctx->challenger, MSG_ERROR, errbuf );
		free( game );
		return;
	}
	game->rounds_per_level = ctx->rounds;
	game->rounds = game->set->count * game->rounds_per_level;
	game->cur_round = -1;

	if ( (game->game = game_create( GT_NETWORK, ctx->diff, 100 )) == 0 ) {

		strncpy(errbuf,"game_create failed: out of memory",128);
		send_info( ctx->challenger, MSG_ERROR, errbuf );
		free( game );
		return;
	}
	game_set_current( game->game );
	game_set_ball_ammo( ctx->balls );
	game_set_frag_limit( ctx->frags );
	game_set_convex_paddle( 1 );
	game_set_ball_random_angle( 1 );


	ctx->challenger->game = game;
	ctx->challenged->game = game;
	ctx->challenger->player_id = 0;
	ctx->challenged->player_id = 1;
	game->users[0] = ctx->challenger;
	game->users[1] = ctx->challenged;


	channel_hide_user( channel, ctx->challenger, 1 );
	channel_hide_user( channel, ctx->challenged, 1 );


	if ( !ctx->challenged->bot ) {
		msg_begin_writing( msgbuf, &msglen, MAX_MSG_SIZE );
		msg_write_int8( MSG_CHALLENGE );
		msg_write_string( ctx->challenger->name );
		msg_write_string( ctx->name );
		msg_write_int8( ctx->diff );
		msg_write_int8( ctx->rounds );
		msg_write_int8( ctx->frags );
		msg_write_int8( ctx->balls );
		socket_transmit( &ctx->challenged->socket, CODE_BLUE, msglen, msgbuf );
	}
	else {

		msgbuf[0] = MSG_ACCEPT_CHALLENGE;
		socket_transmit( &game->users[0]->socket,
			CODE_BLUE, 1, msgbuf );
		init_next_round( game );
	}

	list_add( games, game );
	printf( _("game added: %s (%i): %i rounds: %s vs. %s\n"),
		game->set->name, game->id, game->rounds,
		game->users[0]->name, game->users[1]->name );
}
