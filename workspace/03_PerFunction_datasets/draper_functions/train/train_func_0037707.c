line_check_bar(int *start, int *length, int clipstart, int cliplength)
{
	int overlength;

	if (*start < clipstart) {
		*length -= (clipstart - *start);
		*start = clipstart;
	}

	overlength = 1 + (*start + *length) - (clipstart + cliplength);

	if (overlength > 0)
		*length -= overlength;

	return (*length < 0);
}
