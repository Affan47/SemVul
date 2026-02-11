SetBalanceTeams(bool balanceTeams, NoTeamId noTeamId)
{
	if (balanceTeams==balanceTeamsIsActive)
		return false;

	balanceTeamsIsActive=balanceTeams;


	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_TEAM_BALANCER_INTERNAL);
	bsOut.WriteCasted<MessageID>(ID_RUN_SetBalanceTeams);
	bsOut.Write(GetWorldId());
	bsOut.Write(balanceTeams);
	bsOut.Write(noTeamId);
	GetTeamManager()->SendUnified(&bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, GetHost(), false);

	return true;
}
