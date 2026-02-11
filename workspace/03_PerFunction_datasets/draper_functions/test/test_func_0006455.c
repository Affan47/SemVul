SCR_DrawField (int x, int y, int color, int width, int value, float scale)
{
	char	num[16], *ptr;
	int		l;
	int		frame;

	if (width < 1)
		return;


	if (width > 5)
		width = 5;

	Com_sprintf (num, sizeof(num), "%i", value);
	l = strlen(num);
	if (l > width)
		l = width;
	x += 2 + CHAR_WIDTH*(width - l)*scale;

	ptr = num;
	while (*ptr && l)
	{
		if (*ptr == '-')
			frame = STAT_MINUS;
		else
			frame = *ptr -'0';

		Draw_ScaledPic (x,y,scale/1.8,sb_nums[color][frame]);
		x += CHAR_WIDTH*scale;
		ptr++;
		l--;
	}
}
