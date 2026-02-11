ask_code(char *str)
{
    int ret = 0;

    if (str == NULL)
        return -1;

    if (strlen(str) < 3)
        return -1;


    if ((!isdigit((unsigned char) str[0])) ||
	(!isdigit((unsigned char) str[1])) ||
	(!isdigit((unsigned char) str[2])))
    {
	d_printf(0,
		 "Parse error: response does not begin with a code [%s]\n",
		 str);
	return -1;
    }


    ret = ((str[0]-'0')*100)+
	  ((str[1]-'0')*10)+
	  (str[2]-'0');

    return ret;
}
