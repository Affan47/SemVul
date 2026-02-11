GetColor(char *name)
{
	int i;
	int n;
	int cs;
	char *rest;
	XColor color;

	switch ((i = GetTokenIndex(name, colorset_names, -1, &rest)))
	{
	case 0:
	case 1:
	case 2:
	case 3:
		if (!isdigit(*rest) || (*rest == '0' && *(rest + 1) != 0))
		{

			fprintf(stderr,
				"Invalid colorset number in color '%s'\n",
				name);
			return 0;
		}
		sscanf(rest, "%d%n", &cs, &n);
		if (*(rest + n) != ']')
		{
			fprintf(stderr,
				"No closing brace after '%d' in color '%s'\n",
				cs, name);
			return 0;
		}
		if (*(rest + n + 1) != 0)
		{
			fprintf(stderr, "Trailing characters after brace in"
				" color '%s'\n", name);
			return 0;
		}
		AllocColorset(cs);
		switch (i)
		{
		case 0:
			color.pixel = Colorset[cs].fg;
			break;
		case 1:
			color.pixel = Colorset[cs].bg;
			break;
		case 2:
			color.pixel = Colorset[cs].hilite;
			break;
		case 3:
			color.pixel = Colorset[cs].shadow;
			break;
		}
		if (!PictureAllocColor(Pdpy, Pcmap, &color, True))
		{
			fprintf(stderr, "Cannot allocate color %d from"
				" colorset %d\n", i, cs);
			return 0;
		}
		return color.pixel;

	default:
		break;
	}

	return GetSimpleColor(name);
}
