get_item(char *options, unsigned int &option_ptr,
		     char *key, char *value, struct va_list_passer &vlp)
{

    if (option_ptr+4 >= strlen(options)) return false;


    strncpy(key, &options[option_ptr], 3);
    key[3] = '\0';
    option_ptr += 3;

    SPAN_BLANKS(options, option_ptr);
    if (options[option_ptr] != '=')
    {
	fprintf(stderr, "Error in options string, '=' missing after %s :\n%s\n", key, options);
	return false;
    }
    option_ptr++;
    SPAN_BLANKS(options, option_ptr);


    bool quoted = false;
    char end_char = ',';
    if (options[option_ptr] == '"')
    {
	option_ptr++;
	quoted = true;
	end_char = '"';
    }
    if (options[option_ptr] == '\'')
    {
	option_ptr++;
	quoted = true;
	end_char = '\'';
    }

    int value_ptr = 0;


    while (option_ptr < strlen(options))
    {

	if (options[option_ptr] == '"' &&
	    options[option_ptr+1] == '"')
	{
	    option_ptr++;
	    value[value_ptr++] = '"';
	    continue;
	}


	if (options[option_ptr] == end_char)
	{
	    option_ptr++;
	    break;
	}


	value[value_ptr++] = options[option_ptr++];
    }


    value[value_ptr] = '\0';


    if (value[0] == '%')
    {
	int len = 0;
	int ptr = 1;
	int intval;
	char *charval;

	if (value[1] == '*')
	{
	    ptr++;
	    len = va_arg(vlp.ap, int);
	}
	switch (value[ptr])
	{
	case 'd':


	    intval = va_arg(vlp.ap, int);
	    sprintf(value, "%d", intval);
	    break;

	case 's':
	    charval = va_arg(vlp.ap, char *);
	    if (len)
	    {
		memcpy(value, charval, len);
	    }
	    else
	    {
		strcpy(value, charval);
	    }
	    break;
	}
    }


    SPAN_BLANKS(options, option_ptr);
    if (options[option_ptr] == ',')
	option_ptr++;
    SPAN_BLANKS(options, option_ptr);

    return true;
}
