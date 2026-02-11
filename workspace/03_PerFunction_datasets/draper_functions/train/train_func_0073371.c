update_bot_paddle( Game *game, int ms )
{
	int src_x, dest_x, dir;
	Ball *ball, *min_ball = 0;
	Extra *extra, *min_extra = 0;
	Paddle *paddle = game->paddles[PADDLE_TOP];
	int move = 0;
        static int entropy = 0;
        float change;


	paddle->fire_left = 1;


	list_reset( game->balls );
	while ( ( ball = list_next( game->balls ) ) ) {
		if ( ball->attached ) continue;
		if ( min_ball == 0 || ball->y < min_ball->y )
			min_ball = ball;
	}

	list_reset( game->extras );
	while ( ( extra = list_next( game->extras ) ) ) {
		if ( extra->dir != -1 ) continue;
		if ( min_extra == 0 || extra->y < min_extra->y )
			min_extra = extra;
	}

	src_x = paddle->x + paddle->w/2;
        dest_x = paddle->x + paddle->w/2;
	if ( min_ball || min_extra ) {
		if ( min_ball && ( min_extra == 0 || min_ball->y < min_extra->y ) ) {
			dest_x = min_ball->x + 6;
			move = 1;
		}
		else
		if ( min_extra && ( min_ball == 0 || min_extra->y < min_ball->y ) ) {
			dest_x = min_extra->x + 20;
			move = 1;
		}
	}
	dir = (dest_x<src_x)?-1:(dest_x>src_x)?1:0;

        entropy = (rand() % 17)-8;
	if ( move && dir != 0 ) {
            change = paddle->bot_vx * ms;


            if ( dir < 0 && src_x-change<dest_x+entropy )
                paddle->cur_x = dest_x+entropy - paddle->w/2;
            else
                if ( dir > 0 && src_x+change>dest_x-entropy )
                    paddle->cur_x = dest_x-entropy - paddle->w/2;
                else
                    paddle->cur_x += change * dir;
            if ( paddle->cur_x < BRICK_WIDTH )
                paddle->cur_x = BRICK_WIDTH;
            if ( paddle->cur_x + paddle->w >= 640 - BRICK_WIDTH )
                paddle->cur_x = 640 - BRICK_WIDTH - paddle->w;
            paddle->x = (int)paddle->cur_x;
	}
}
