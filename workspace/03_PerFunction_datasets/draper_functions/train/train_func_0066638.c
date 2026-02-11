next_field(const char **p, const char **start,
    const char **end, char *sep)
{

	while (**p == ' ' || **p == '\t' || **p == '\n') {
		(*p)++;
	}
	*start = *p;


	while (**p != '\0' && **p != ',' && **p != ':' && **p != '\n') {
		(*p)++;
	}
	*sep = **p;


	*end = *p - 1;
	while (**end == ' ' || **end == '\t' || **end == '\n') {
		(*end)--;
	}
	(*end)++;


	if (**p != '\0')
		(*p)++;
}
