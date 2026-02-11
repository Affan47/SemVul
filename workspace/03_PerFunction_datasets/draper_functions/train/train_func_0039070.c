handle_mods()
{
	BrickHit *brickhits;
	int *extras, count;
	int i, j;

#ifdef AUDIO_ENABLED


    if ( local_game == 0 )
    {
        if ( game_get_fired_shot_count() )
            stk_sound_play( wav_shot );
        if ( game_get_brick_reflected_ball_count() )
            stk_sound_play( wav_reflect_brick );
        if ( game_get_paddle_reflected_ball_count() )
            stk_sound_play( wav_reflect_paddle );
        if ( game_get_attached_ball_count() )
            stk_sound_play( wav_attach );
    }
    else
    {
        if ( last_ball_brick_reflect_x != -1 )
            stk_sound_play_x( last_ball_brick_reflect_x, wav_reflect_brick );
        if ( last_ball_paddle_reflect_x != -1 )
            stk_sound_play_x( last_ball_paddle_reflect_x, wav_reflect_paddle );
        if ( last_ball_attach_x != -1 )
            stk_sound_play_x( last_ball_attach_x, wav_attach );
        if ( last_shot_fire_x != -1 )
            stk_sound_play_x( last_shot_fire_x, wav_shot );
        last_ball_brick_reflect_x = -1;
        last_ball_paddle_reflect_x = -1;
        last_ball_attach_x = -1;
        last_shot_fire_x = -1;
    }
#endif


	brickhits = game_get_brick_hits( &count );
	for ( i = 0; i < count; i++ )
		client_handle_brick_hit( &brickhits[i] );


	for ( i = 0; i < game->paddle_count; i++ ) {
		extras = game_get_collected_extras( i, &count );
		for ( j = 0; j < count; j++ )
			client_handle_collected_extra( game->paddles[i], extras[j] );
	}

	game_reset_mods();
}
