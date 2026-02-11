ball_wall_collision(Game *game, Ball *ball) {
	gboolean ball_dead = FALSE;

	if(ball->geometry.x1 < 0) {
		if(ball->geometry.y1 < 0) {
			recalculate_ball_trajectory(game, ball, SIDE_DIAGONAL);
		} else {
			recalculate_ball_trajectory(game, ball, SIDE_RIGHT);
		}
	} else if(ball->geometry.x2 > GAME_WIDTH) {
		if(ball->geometry.y1 < 0) {
			recalculate_ball_trajectory(game, ball, SIDE_DIAGONAL);
		} else {
			recalculate_ball_trajectory(game, ball, SIDE_LEFT);
		}
	} else if(ball->geometry.y1 < 0) {
		recalculate_ball_trajectory(game, ball, SIDE_BOTTOM);
	} else if(ball->geometry.y2 > GAME_HEIGHT) {
		ball_dead = TRUE;
	}


	return ball_dead;
}
