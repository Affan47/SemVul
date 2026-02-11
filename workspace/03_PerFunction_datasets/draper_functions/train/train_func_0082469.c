cmd_setplan4()
{
	if(!cmdinfo.isparam)
	{
		say("Usage: setplan4 <plan>");
		sayf(2,0,"Use this command to set plan line 4.  Specify 'none' to erase it.");
		return;
	}


	if(isequal(cmdinfo.param,"none"))
	{
		xfree(cmdinfo.user->plan4);
		cmdinfo.user->plan4 = NULL;
		say("Plan line 4 erased.");
		return;
	}

	cmd_setplan_helper(4);
	say("Plan line 4 set.  Thanks!");
}
