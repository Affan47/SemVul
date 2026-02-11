GetDiscKey(int agid,unsigned char *key)
{
	unsigned char cmd[12],buf[2052],*keyval;
	int index;

	memset(cmd,0,sizeof(cmd));
	memset(buf,0,2052);
	cmd[ 0] = 0xAD;
	cmd[ 7] = 0x02;
	cmd[ 8] = 2052 >> 8;
	cmd[ 9] = 2052 & 0xFF;
	cmd[10] = agid << 6;
	keyval = buf + 4;
	if (bdev->scsi(cmd,12,buf,2052,1) < 0) {

		return 0;
	}

	for (index=0;index < 2048;index++)
		keyval[index] ^= key[4 - (index%5)];

	bitch(BITCHINFO,"Attempting to find disc key...");
	if (DecryptDiscKey(keyval,DiscKey) < 0) {
		bitch(BITCHWARNING,"Unable to find disc key!");
		return 0;
	}

	bitch(BITCHINFO,"Found disc key: %02X %02X %02X %02X %02X",
			DiscKey[0],
			DiscKey[1],
			DiscKey[2],
			DiscKey[3],
			DiscKey[4]);

	have_disc_key = 1;
	return 1;
}
