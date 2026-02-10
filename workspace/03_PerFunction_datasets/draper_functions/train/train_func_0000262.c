init_next_round( ServerGame *game )
{
	game->cur_round++;
	game->cur_level = game->cur_round / game->rounds_per_level;
	game_init( game->game, game->set->levels[game->cur_level] );


	game->state = SERVER_AWAIT_READY;
	game->ready[0] = game->ready[1] = 0;
	send_level( game->set->levels[game->cur_level],
			game->users[0], PADDLE_BOTTOM );
	if ( !game->users[1]->bot )
		send_level( game->set->levels[game->cur_level],
			game->users[1], PADDLE_TOP );
	else
		game->ready[1] = 1;


        if ( game->users[1]->bot )
            game->game->paddles[PADDLE_TOP]->bot_vx =
                0.001 * game->users[1]->bot_level;

}
