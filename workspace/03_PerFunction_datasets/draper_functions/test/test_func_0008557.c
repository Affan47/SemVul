cli_isnumber(const char *str)
{
    while(*str)
	if(!strchr("0123456789", *str++))
	    return 0;

    return 1;
}
