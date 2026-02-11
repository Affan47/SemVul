intif_parse_PartyMemberAdded(int fd)
{
	if(battle_config.etc_log)
		printf("intif: party member added %d %d %d %-24s\n",RFIFOL(fd,2),RFIFOL(fd,6),RFIFOB(fd,14),RFIFOP(fd,15));
	party_member_added(RFIFOL(fd,2),RFIFOL(fd,6),RFIFOL(fd,10),RFIFOB(fd,14));

	return;
}
