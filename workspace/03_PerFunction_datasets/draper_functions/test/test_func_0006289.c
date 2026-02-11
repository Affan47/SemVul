metamrph_sprite_callback(int *code, int *color, int *priority)
{
	int c = *color;
	int attr = c;

	c = (c & 0x1f) | sprite_colorbase;


	if ((attr & 0x300) != 0x300)
	{
		*color = c;
		*priority = (attr & 0xe0) >> 2;
	}
	else
	{
		*color = c | 3<<K055555_MIXSHIFT | K055555_SKIPSHADOW;
		*priority = 0x1c;
	}
}
