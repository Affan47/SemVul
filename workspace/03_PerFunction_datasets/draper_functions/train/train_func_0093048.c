TeamWouldBeUnderpopulatedOnLeave(TeamId teamId, unsigned int teamMemberSize)
{
	if (forceTeamsToBeEven)
	{
		unsigned int minMembersOnASingleTeam = (teamMemberSize-1)/teamLimits.Size();
		return teamMemberCounts[teamId]<=minMembersOnASingleTeam;
	}
	return false;
}
