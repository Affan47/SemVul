paddle_resize( Paddle *paddle, int ms )
{
	if ( paddle->w == paddle->wanted_w ) return 0;
	if ( !delay_timed_out( &paddle->resize_delay, ms ) ) return 0;

	if ( paddle->w < paddle->wanted_w ) {
		paddle->w += 2;
		paddle->cur_x -= 1;
		paddle->x = (int)paddle->cur_x;

		if (paddle->x < BRICK_WIDTH)
			paddle->x = BRICK_WIDTH;
		if (paddle->x + paddle->w > 640 - BRICK_WIDTH)
			paddle->x = 640 - BRICK_WIDTH - paddle->w;
		return 1;
	}
	else {
		paddle->w -= 2;
		paddle->cur_x += 1;
		paddle->x = (int)paddle->cur_x;
		return -1;
	}
}
