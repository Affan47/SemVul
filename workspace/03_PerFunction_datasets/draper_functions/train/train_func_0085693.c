ball_block_collision(Game *game, Ball *ball) {
	Side side;
	Block *block;
	gboolean rval = FALSE;

	block = find_block_from_position(game, (Entity *) ball);
	if(block) {
		hit_block(game, block);
		side = find_hit_side(ball, (Entity *) block);
		if(side == SIDE_DIAGONAL)
			side = find_block_hit_side(game, block, ball);
		increase_ball_speed(game, ball);
		recalculate_ball_trajectory(game, ball, side);
		rval = TRUE;
	}
	return rval;
}
