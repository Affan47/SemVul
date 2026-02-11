bricks_init_next_wave( Game *game )
{
	if (game->blNumCompletedRuns==0)
	{
		game->blInvaderLimit= 50;
		if (game->blInvaders) free(game->blInvaders);
		game->blInvaders = (Invader*)calloc(game->blInvaderLimit,sizeof(Invader));
	}
	game->blInvaderTime = game->blActionTime;
	game->blNumInvaders = 0;
	game->blNumKilledInvaders = 0;
	game->blInvadersWaveOver = 0;
	delay_set(&game->blDelay,game->blInvaderTime);
	bricks_add_invader(game,&game->blInvadersWaveOver);
	bricks_add_invader(game,&game->blInvadersWaveOver);
	bricks_add_invader(game,&game->blInvadersWaveOver);
}
