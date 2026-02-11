ball_handle_paddle_contact( Ball *ball, Paddle *paddle, Vector perp_vector )
{
	float  old_vx = ball->vel.x;
	Vector c;

	ball->paddle = paddle;


	if ( perp_vector.x == 0 && perp_vector.y == 0 )
		return;


	c.x = (1-2*perp_vector.x*perp_vector.x)*ball->vel.x +
	      ( -2*perp_vector.x*perp_vector.y)*ball->vel.y;
	c.y = ( -2*perp_vector.x*perp_vector.y)*ball->vel.x +
	      (1-2*perp_vector.y*perp_vector.y)*ball->vel.y;


	if ( (paddle->type == PADDLE_TOP && c.y < 0) ||
  	     (paddle->type == PADDLE_BOTTOM && c.y > 0) )
		return;


	ball->vel.x = c.x; ball->vel.y = c.y;
#ifdef PADDLE_FRICTION

	if ( cur_game->paddle_is_convex )
		ball->vel.x += paddle->v_x * paddle->friction;
#endif
	ball_mask_vel( ball, old_vx, BALL_NO_ENTROPY );

	ball->angle = vec2angle( &ball->vel );
	angle2vec( ball->angle, &ball->vel );
	vector_set_length( &ball->vel, cur_game->ball_v );


	if ( ball->x < BRICK_WIDTH ) {
		ball->cur.x = BRICK_WIDTH;
		ball->x = (int)ball->cur.x;
	}
	else
		if ( ball->x + ball_dia >= 640 - BRICK_WIDTH ) {
			ball->cur.x = 640 - BRICK_WIDTH - ball_dia;
			ball->x = (int)ball->cur.x;
		}
	if ( paddle->extra_active[EX_WALL] ) {
		if ( paddle->type == PADDLE_BOTTOM ) {
			if ( ball->cur.y + ball_dia > 480 - BRICK_HEIGHT - 1 ) {
				ball->cur.y = 480 - BRICK_HEIGHT - 1 - ball_dia;
				ball->y = (int)ball->cur.y;
			}
		}
		else {
			if ( ball->cur.y < BRICK_HEIGHT ) {
				ball->cur.y = BRICK_HEIGHT;
				ball->y = (int)ball->cur.y;
			}
		}
	}


	if ( paddle_slimy( paddle ) ) {
		ball_attach( ball, paddle );
		return;
	}


	paddle->balls_reflected++;
	cur_game->mod.paddle_reflected_ball_count++;
        last_ball_paddle_reflect_x = ball->x;


	ball->get_target = 1;


	paddle->last_ball_contact = SDL_GetTicks();
}
