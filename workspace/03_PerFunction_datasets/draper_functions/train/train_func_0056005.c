paddle_init_resize( Paddle *paddle, int c )
{

	if ( paddle->len + c > paddle->max_len || paddle->len + c < paddle->min_len )
		return 0;

	paddle->len += c;
	paddle->wanted_w = (paddle->len + 2) * paddle_cw;

	delay_reset( &paddle->resize_delay );
	return 1;
}
