_cl5WriteString (const char *str, char **buff)
{
	if (str)
	{
		strcpy (*buff, str);
		(*buff) += strlen (str) + 1;
	}
	else
	{
		(**buff) = '\0';
		(*buff) ++;
	}
}
