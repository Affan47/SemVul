sprintf_puts(char **b, char *blimit, const char *buf)
{
	while (*b < blimit && *buf) {
		**b = *(buf++);
		(*b)++;
	}
}
