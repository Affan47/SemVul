mca_opt_first_char(c)
    int c;
{
	int flag = (optflag & ~OPT_NO_PROMPT);
	if (flag == OPT_NO_TOGGLE)
	{
		switch (c)
		{
		case '_':

			optgetname = TRUE;
			mca_opt_toggle();
			return (MCA_MORE);
		}
	} else
	{
		switch (c)
		{
		case '+':

			optflag = (flag == OPT_UNSET) ?
				OPT_TOGGLE : OPT_UNSET;
			mca_opt_toggle();
			return (MCA_MORE);
		case '!':

			optflag = (flag == OPT_SET) ?
				OPT_TOGGLE : OPT_SET;
			mca_opt_toggle();
			return (MCA_MORE);
		case CONTROL('P'):
			optflag ^= OPT_NO_PROMPT;
			mca_opt_toggle();
			return (MCA_MORE);
		case '-':

			optgetname = TRUE;
			mca_opt_toggle();
			return (MCA_MORE);
		}
	}

	return (NO_MCA);
}
