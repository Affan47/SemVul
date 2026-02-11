SetColor(int colorId)
{
	long foregroundPixel;
	long backgroundPixel;


	if ((colorId < 0) || (colorId >= MAX_COLORS))
		colorId = DEFAULT_COLOR_ID;

	foregroundPixel = foregroundColorTable[colorId];
	backgroundPixel = backgroundColorTable[colorId];


	if (foregroundPixel != currentForegroundPixel)
		XSetForeground(display, textGC, foregroundPixel);

	if (backgroundPixel != currentBackgroundPixel)
	{
		XSetBackground(display, textGC, backgroundPixel);
		XSetForeground(display, clearGC, backgroundPixel);
	}


	currentForegroundPixel = foregroundPixel;
	currentBackgroundPixel = backgroundPixel;
	currentColorFlags = colorFlagsTable[colorId];
}
