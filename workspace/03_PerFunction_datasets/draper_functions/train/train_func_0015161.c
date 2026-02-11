jambu_tag_verification(const unsigned int *rk, uint64_t msglen, const uint8_t *c, unsigned int *stateS, unsigned int *stateR)
{
	uint8_t t[8];
	int check = 0;
	int i;

	AESEncrypt(rk, stateS);
	stateS[0] ^= stateR[0] ^ 0x03;
	stateS[1] ^= stateR[1];

	stateR[0] ^= stateS[2];
	stateR[1] ^= stateS[3];

	AESEncrypt(rk, stateS);

	((unsigned int *)t)[0] = stateS[0] ^ stateS[2] ^ stateR[0];
	((unsigned int *)t)[1] = stateS[1] ^ stateS[3] ^ stateR[1];
	for (i = 0; i  < 8; i++) check |= (c[msglen+i] ^ t[i]);
	if (0 == check) return 0; else return -1;
}
