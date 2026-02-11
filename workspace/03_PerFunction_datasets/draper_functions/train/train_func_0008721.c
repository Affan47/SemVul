smbdes_lmpwdhash(const char *password, uint8_t *lmhash)
{
	int i;
	uint8_t p14[14];
	static uint8_t sp8[8] = {0x4b, 0x47, 0x53, 0x21, 0x40, 0x23, 0x24, 0x25};

	memset(p14, 0, sizeof(p14));
	for (i = 0; i < 14 && password[i]; i++) {
		p14[i] = toupper((int) password[i]);
	}

	smbhash(lmhash, sp8, p14);
	smbhash(lmhash+8, sp8, p14+7);
}
