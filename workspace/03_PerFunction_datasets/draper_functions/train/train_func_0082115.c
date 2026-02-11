cmd_setvar()
{
	int x;
	char var[STDBUF], param[STDBUF];

	context;
	if(!cmdinfo.isparam)
	{
		say("Usage: setvar <variable> [value]");
		sayf(2,0,"Use this command to set an internal variable.  Leave off the value argument to display the current value.  Use 'configinfo' to display all configuration variables.");
		return;
	}

	context;
	if(!cmdinfo.istok2)
	{
		char	ret[BUFSIZ];
		if(!Grufti_displayvar(cmdinfo.tok1,ret))
			say("No such variable \"%s\".  Use 'configinfo' to show all configuration variables.",cmdinfo.tok1);
		else
			say("%s is %s",cmdinfo.tok1,ret);
		return;
	}

	context;
	strcpy(param, cmdinfo.param);
	split(var, param);
	x = Grufti_setvar(var, param);
	if(x < 0)
	{
		if(x == -1)
			sayf(0,0,"Unable to set variable: %s.",var);
		else if(x == -2)
			sayf(0,0,"Argument not quoted.  (eg. setvar nick \"Grufti\")");
		else if(x == -3)
			sayf(0,0,"No such variable: %s", var);
		return;
	}

	sayf(0,0,"%s set to \"%s\".",var, param);

	context;
	if(isequal(var,"telnet-port"))
	{

		dccrec *d;

		d = DCC_dccserverbyname("Server001");
		if(d != NULL)
			DCC_disconnect(d);

		DCC_addnewconnection("Server001",Grufti->botuh,0,0,Grufti->reqd_telnet_port,DCC_SERVER|SERVER_PUBLIC);
	}
	else if(isequal(var,"gateway-port"))
	{

		dccrec	*d;

		d = DCC_dccserverbyname("Server002");
		if(d != NULL)
			DCC_disconnect(d);

		DCC_addnewconnection("Server002",Grufti->botuh,0,0,Grufti->reqd_gateway_port,DCC_SERVER|SERVER_INTERNAL);
	}
	else if(isequal(var,"nick"))
		Server_nick(Grufti->botnick);
}
