pum_enough_matches()
{
    compl_T     *compl;
    int		i;


    compl = compl_first_match;
    i = 0;
    do
    {
	if (compl == NULL
		      || ((compl->cp_flags & ORIGINAL_TEXT) == 0 && ++i == 2))
	    break;
	compl = compl->cp_next;
    } while (compl != compl_first_match);

    if (strstr((char *)p_cot, "menuone") != NULL)
	return (i >= 1);
    return (i >= 2);
}
