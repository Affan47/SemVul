SCR_DrawCenterString (void)
{
	char	*start, saved_byte;
	int		l, x, y, maxChars;
	float	alpha = 1.0f;


	start = scr_centerstring;

	if (scr_center_lines <= 4)
		y = (int)(viddef.height*0.35f);
	else
		y = 48;


	alpha = SCR_FadeAlpha(scr_centertime_start, scr_centertime_off - scr_centertime_start, 1000);
	maxChars = (viddef.width >> 3) - 2;

	do
	{

		for (l = 0; l < maxChars; l++) {
			if (start[l] == '\n' || !start[l])
				break;
		}
		x = (viddef.width - l*8)*0.5f;
		SCR_AddDirtyPoint (x, y);

		saved_byte = start[l];
		start[l] = 0;
		Draw_String(x, y, start, COLOR_WHITE, alpha, false);
		start[l] = saved_byte;

		y += 8;
		SCR_AddDirtyPoint (x, y);

		start += l;
		if (!*start)
			break;

		start++;
	}
	while (*start);
}
