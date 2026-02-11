eat_re(char *str)
{
    long	n;

    while ((str[0] == 'R' || str[0] == 'r') &&
	   (str[1] == 'E' || str[1] == 'e')) {
	if (str[2] == ':')
	    str += 3;
	else if (str[2] == '^' && IS_DIGIT(str[3]) && str[4] == ':')
	    str += 5;
	else
	    break;

	while (*str == ' ')
	    str++;
    }

    n = strlen(str) - 1;
    while (n > 0 && IS_SPACE(str[n]))
	str[n--] = '\0';

    return str;
}
