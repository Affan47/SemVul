RemoveFromRequestedTeams(TM_Team *team)
{
	if (team==0)
	{
		teamsRequested.Clear(true, _FILE_AND_LINE_);
		joinTeamType=JOIN_NO_TEAM;
		return true;
	}
	else
	{
		unsigned int i;
		for (i=0; i < teamsRequested.Size(); i++)
		{
			if (teamsRequested[i].requested==team)
			{
				teamsRequested.RemoveAtIndex(i);
				if (teamsRequested.Size()==0)
				{
					joinTeamType=JOIN_NO_TEAM;
				}
				return true;
			}
		}
	}
	return false;
}
