Grufti_checkcrucial(int *errors)
{
	*errors = 0;

	if(!Grufti->botnick[0])
	{
		warning("Crucial config entry not set: nick");
		(*errors)++;
	}


	if(Grufti->botnick[0] && invalidnick(Grufti->botnick))
	{
		warning("Invalid bot nick: %s", Grufti->botnick);
		(*errors)++;
	}

	if(!Grufti->botusername[0])
	{
		warning("Crucial config entry not set: username");
		(*errors)++;
	}

	if(!Grufti->botrealname[0])
	{
		warning("Crucial config entry not set: realname");
		(*errors)++;
	}

	if(!Grufti->userfile[0])
	{
		warning("Crucial config entry not set: userfile");
		(*errors)++;
	}
}
