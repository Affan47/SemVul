opt_Z(type, s)
	int type;
	char *s;
{
	switch (type)
	{
	case INIT:
		if (opt_Z_var == OPT_ON)
			init_def_priority(PSJIS);
		else if (opt_Z_var == OPT_OFF)
			init_def_priority(PUJIS);
		break;
	case QUERY:
		break;
	case TOGGLE:
		switch (get_priority(get_mulbuf(curr_ifile))) {
		case PSJIS:
			opt_Z_var = OPT_OFF;
			break;
		case PUJIS:
			opt_Z_var = OPT_ON;
			break;
		case PNONE:
		default:
			opt_Z_var = OPT_ONPLUS;
			return;
		}
		if (opt_Z_var == OPT_ON)
			init_def_priority(PSJIS);
		else if (opt_Z_var == OPT_OFF)
			init_def_priority(PUJIS);
		init_priority(get_mulbuf(curr_ifile));
		break;
	}
}
