GMT_get_char_encoding (char *name)
{
	short int i;

	for (i = 0; i < 7 && strcmp (name, GMT_weekdays[i]); i++);
	return (i);
}
