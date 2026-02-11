intif_parse_PartyInfo(int fd)
{
	if( RFIFOW(fd,2)==8){
		if(battle_config.error_log)
			printf("intif: party noinfo %d\n",RFIFOL(fd,4));
		party_recv_noinfo(RFIFOL(fd,4));
		return 0;
	}

	if( RFIFOW(fd,2)!=sizeof(struct party)+4 ){
		if(battle_config.error_log)
			printf("intif: party info : data size error %d %d %lu\n",RFIFOL(fd,4),RFIFOW(fd,2),(unsigned long)(sizeof(struct party)+4));
	}
	party_recv_info((struct party *)RFIFOP(fd,4));
	return 0;
}
