somethingToDoWithSpaces(const char *const buf, char **const ptr)
{
	if (*buf != 0 && isspace((int)*buf)) {
		while (**ptr != 0 && !isspace((int)**ptr)) {
			(*ptr)++;
		}
	}
}
