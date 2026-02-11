GetCDCapacity(JarchSession *session)
{
	unsigned char cmd[10],buf[8];
	unsigned long x;
	int i;

	cmd[0] = 0x25;
	cmd[1] = 0x00;
	cmd[2] =
	cmd[3] =
	cmd[4] =
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	cmd[8] = 0;
	cmd[9] = 0;
	if (session->bdev->scsi(cmd,10,buf,sizeof(buf),1) < 0) {
		bitch(BITCHERROR,"Unable to read DVD capacity");
		return;
	}

	x = binBeHe32(buf+4);
	if (x != 2048) {
		bitch(BITCHERROR,"Sector size != 2048. I cannot rip this!");
		return;
	}

	x = session->CD_capacity = binBeHe32(buf);
	bitch(BITCHINFO,"Obtained DVD capacity as %u",x);

	for (i=0;i < 32;i++)
		session->todo->set(TODO_RIPDVD_CAPACITY_DWORD+i,(x >> i) & 1);

	session->todo->set(TODO_RIPDVD_READCAPACITY,1);
}
