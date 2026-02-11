intif_parse_WisEnd(int fd)
{
	struct map_session_data* sd = map_nick2sd(RFIFOP(fd,2));
	struct map_session_data* ssd = map_nick2sd(RFIFOP(fd,26));

	if(sd) {
		if(ssd)
			clif_wis_end(sd->fd,RFIFOB(fd,50),ssd->char_id);
		else
			clif_wis_end(sd->fd,RFIFOB(fd,50),0);
	}
	return 0;
}
