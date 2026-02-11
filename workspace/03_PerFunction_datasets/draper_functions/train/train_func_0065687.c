make_upper(char *str)
{
    unsigned int i;

    for (i=0; i<strlen(str); i++)
    {
	str[i] = toupper(str[i]);
    }
}
