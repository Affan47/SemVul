InitializeState(unsigned char *state, unsigned char *key, unsigned char *nonce)
{
	GenerateRoundConstants();

	for(int i=0; i<RateSizeElements; i++)
		state[i]=0;
	for(int i=0; i<KeySizeElements; i++)
		state[RateSizeElements+i]=key[i];
	for(int i=0; i<NonceSizeElements; i++)
		state[(RateSizeElements+KeySizeElements)+i]=nonce[i];
}
