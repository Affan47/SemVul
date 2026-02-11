c_skip_space(void)
{
	char c;

	if ((c = c_getchar(0)) == ' ') c = c_getchar(0);

	return c;
}
