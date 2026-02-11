ign_add (char *ign, int hold)
{
    if (!ign || !*ign)
	return;

    for (; *ign; ign++)
    {
	char *mark;
	char save;


	if (isspace ((unsigned char) *ign))
	    continue;


	if (ign_count >= ign_size)
	{
	    ign_size += IGN_GROW;
	    ign_list = xnrealloc (ign_list, ign_size + 1, sizeof (char *));
	}


	if ((!*(ign+1) || isspace ((unsigned char) *(ign+1)))
	    && (*ign == '!' || *ign == '*'))
	{
	    if (!hold)
	    {

		int i;

		for (i = 0; i < ign_count; i++)
		    free (ign_list[i]);
		ign_count = 1;

		ign_list[0] = xstrdup ("CVS");
		ign_list[1] = NULL;


		if (*ign == '!')
		{
		    ign_inhibit_server = 1;
		    continue;
		}
	    }
	    else if (*ign == '!')
	    {

		int i;

		if (ign_hold >= 0)
		{
		    for (i = ign_hold; i < ign_count; i++)
			free (ign_list[i]);
		    ign_hold = -1;
		}
		if (s_ign_list)
		{


		    for (i = 0; i < ign_count; i++)
			free (ign_list[i]);
		}
		else
		{

		    s_ign_list = xnmalloc (ign_count, sizeof (char *));
		    for (i = 0; i < ign_count; i++)
			s_ign_list[i] = ign_list[i];
		    s_ign_count = ign_count;
		}
		ign_count = 1;

		ign_list[0] = xstrdup ("CVS");
		ign_list[1] = NULL;
		continue;
	    }
	}


	for (mark = ign; *mark && !isspace ((unsigned char) *mark); mark++)
	      ;

	save = *mark;
	*mark = '\0';

	ign_list[ign_count++] = xstrdup (ign);
	ign_list[ign_count] = NULL;

	*mark = save;
	if (save)
	    ign = mark;
	else
	    ign = mark - 1;
    }
}
