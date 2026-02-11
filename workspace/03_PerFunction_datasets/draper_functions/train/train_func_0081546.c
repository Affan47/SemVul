EvenTeams(void)
{

	int minMembersOnASingleTeam;
	int maxMembersOnASingleTeam;
	GetMinMaxTeamMembers(minMembersOnASingleTeam,maxMembersOnASingleTeam);


	DataStructures::List<TeamId> overpopulatedTeams;
	TeamId teamMemberCountsIndex;
	unsigned int memberIndexToSwitch;
	for (teamMemberCountsIndex=0; teamMemberCountsIndex<teamMemberCounts.Size(); teamMemberCountsIndex++)
	{
		while (teamMemberCounts[teamMemberCountsIndex]<minMembersOnASingleTeam && teamMemberCounts[teamMemberCountsIndex]<teamLimits[teamMemberCountsIndex])
		{
			GetOverpopulatedTeams(overpopulatedTeams,maxMembersOnASingleTeam);
			RakAssert(overpopulatedTeams.Size()>0);
			memberIndexToSwitch=GetMemberIndexToSwitchTeams(overpopulatedTeams,teamMemberCountsIndex);
			RakAssert(memberIndexToSwitch!=(unsigned int)-1);
			SwitchMemberTeam(memberIndexToSwitch,teamMemberCountsIndex);

			NotifyTeamAssigment(memberIndexToSwitch);
		}
	}
}
