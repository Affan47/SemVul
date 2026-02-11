getbgc (bool blank)
{
#if 0
	if (blank)
		return xcolors[0x088];
	else if (hposblank == 1)
		return xcolors[0xf00];
	else if (hposblank == 2)
		return xcolors[0x0f0];
	else if (hposblank == 3)
		return xcolors[0x00f];
	else if (brdblank)
		return xcolors[0x880];

	return xcolors[0xf0f];
#endif
	return (blank || hposblank || colors_for_drawing.borderblank) ? 0 : colors_for_drawing.acolors[0];
}
