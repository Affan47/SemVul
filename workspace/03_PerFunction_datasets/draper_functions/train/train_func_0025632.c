TapeSliderLabel(char *label, int value, void *user_data)
{
	if (value >= CASSETTE_GetSize())
		sprintf(label, "End");
	else
		snprintf(label, 10, "%i", value + 1);
}
