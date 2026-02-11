mode_has_arg (server * serv, char sign, char mode)
{
	int type;


	if (strchr (serv->nick_modes, mode))
		return 1;

	type = mode_chanmode_type (serv, mode);
	switch (type)
	{
	case 0:
	case 1:
		return 1;
	case 2:
		if (sign == '+')
			return 1;
	case 3:
		return 0;
	default:
		return 0;
	}

}
