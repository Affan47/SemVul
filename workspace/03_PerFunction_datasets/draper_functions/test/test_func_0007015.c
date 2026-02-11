font_component (char const *fontname, int idx)
{
	int i = 0;
	char const *p = fontname;

	for (; *p && i < idx; p++) {
		if (*p == '-')
			i++;
	}
	if (*p == '-')
		p++;

	return p;
}
