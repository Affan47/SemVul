eval3(arg, rettv, evaluate)
    char_u	**arg;
    typval_T	*rettv;
    int		evaluate;
{
    typval_T	var2;
    long	result;
    int		first;
    int		error = FALSE;


    if (eval4(arg, rettv, evaluate) == FAIL)
	return FAIL;


    first = TRUE;
    result = TRUE;
    while ((*arg)[0] == '&' && (*arg)[1] == '&')
    {
	if (evaluate && first)
	{
	    if (get_tv_number_chk(rettv, &error) == 0)
		result = FALSE;
	    clear_tv(rettv);
	    if (error)
		return FAIL;
	    first = FALSE;
	}


	*arg = skipwhite(*arg + 2);
	if (eval4(arg, &var2, evaluate && result) == FAIL)
	    return FAIL;


	if (evaluate && result)
	{
	    if (get_tv_number_chk(&var2, &error) == 0)
		result = FALSE;
	    clear_tv(&var2);
	    if (error)
		return FAIL;
	}
	if (evaluate)
	{
	    rettv->v_type = VAR_NUMBER;
	    rettv->vval.v_number = result;
	}
    }

    return OK;
}
