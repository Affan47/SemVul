get_bool(const char *str)
{
    if (str[0] == 'y' || str[0] == 'Y')
	return (1);
    if (str[0] == 'n' || str[0] == 'N')
	return (0);

    return (atoi(str) ? 1 : 0);
}
