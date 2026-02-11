AllocateColor(const char * color)
{
	char *		dupColor;
	char *		slash;
	const char *	foreground;
	const char *	background;
	const char *	flagsString;
	ColorData *	pair;
	int		colorFlags;
	int		colorId;


	dupColor = strdup(color);

	if (dupColor == 0)
		return BAD_COLOR_ID;

	foreground = dupColor;
	background = "";
	flagsString = "";

	slash = strchr(dupColor, '/');

	if (slash)
	{
		*slash++ = '\0';
		background = slash;
	}

	if (slash)
		slash = strchr(slash, '/');

	if (slash)
	{
		*slash++ = '\0';
		flagsString = slash;
	}


	colorFlags = COLOR_FLAG_NONE;

	while (*flagsString)
	{
		switch (*flagsString++)
		{
			case 'u':
				colorFlags |= COLOR_FLAG_UNDERLINE;
				break;

			case 'b':
				colorFlags |= COLOR_FLAG_BOLD;
				break;

			default:
				return BAD_COLOR_ID;
		}
	}


	if (strcmp(foreground, DEFAULT_COLOR_NAME) == 0)
		foreground = "";

	if (strcmp(background, DEFAULT_COLOR_NAME) == 0)
		background = "";


	for (colorId = 0; colorId < colorCount; colorId++)
	{
		pair = &colorTable[colorId];

		if ((strcmp(pair->foreground, foreground) == 0) &&
			(strcmp(pair->background, background) == 0) &&
			(pair->flags == colorFlags))
		{
			return colorId;
		}
	}


	if (colorCount >= MAX_COLORS)
	{
		free(dupColor);

		return BAD_COLOR_ID;
	}

	pair = &colorTable[colorCount];

	pair->foreground = foreground;
	pair->background = background;
	pair->flags = colorFlags;

	return colorCount++;
}
