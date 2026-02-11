get_list_range(str, num1, num2)
    char_u	**str;
    int		*num1;
    int		*num2;
{
    int		len;
    int		first = FALSE;
    long	num;

    *str = skipwhite(*str);
    if (**str == '-' || vim_isdigit(**str))
    {
	vim_str2nr(*str, NULL, &len, FALSE, FALSE, &num, NULL);
	*str += len;
	*num1 = (int)num;
	first = TRUE;
    }
    *str = skipwhite(*str);
    if (**str == ',')
    {
	*str = skipwhite(*str + 1);
	vim_str2nr(*str, NULL, &len, FALSE, FALSE, &num, NULL);
	if (len > 0)
	{
	    *num2 = (int)num;
	    *str = skipwhite(*str + len);
	}
	else if (!first)
	    return FAIL;
    }
    else if (first)
	*num2 = *num1;
    return OK;
}
