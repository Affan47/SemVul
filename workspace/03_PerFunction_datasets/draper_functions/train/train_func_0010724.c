get_expr_line()
{
    char_u	*expr_copy;
    char_u	*rv;
    static int	nested = 0;

    if (expr_line == NULL)
	return NULL;


    expr_copy = vim_strsave(expr_line);
    if (expr_copy == NULL)
	return NULL;


    if (nested >= 10)
	return expr_copy;

    ++nested;
    rv = eval_to_string(expr_copy, NULL, TRUE);
    --nested;
    vim_free(expr_copy);
    return rv;
}
