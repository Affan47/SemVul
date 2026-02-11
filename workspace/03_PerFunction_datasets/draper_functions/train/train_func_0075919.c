ct_checkinput_req(void)
{
	unsigned char	msg[8] = {0x09,0x00,0x04,0x00,0x0D,0x00,0x00,0x00};
	short 	*p = (void *)&msg[4];
        if (debug == 2) { printf(" Entered static void ct_checkinput_req...\n");}

	set_short(p, aheadcnt+inpcnt);
	if (write(sockfd,msg,8) < 0)
	{
		perror("input count msg");
		ct_reset_term();
		exit(-1);
	}
}
