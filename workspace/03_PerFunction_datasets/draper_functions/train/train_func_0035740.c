ISODVDVideoDecrypt(unsigned long sector,unsigned char *data,int N,unsigned char *keydata)
{
	unsigned char *key = keydata + 1;
	int x,d=0;

	if (key[0] == 0x00 && key[1] == 0x00 && key[2] == 0x00 && key[3] == 0x00 && key[4] == 0x00)
		return 0;

	for (x=0;x < N;x++,data += 2048) {
		if (data[0] == 0 && data[1] == 0 && data[2] == 1 && data[3] == 0xBA) {
			if (data[0x14] & 0x30) {
				CSS_unscramble(data,key);
				data[0x14] &= ~0x30;
				d++;
			}
		}
	}

	return d;
}
