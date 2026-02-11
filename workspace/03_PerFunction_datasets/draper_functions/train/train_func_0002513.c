process_ad(ae_cxt* cxt, const byte* ad, unsigned long long adlen, const byte* nonce, unsigned long long nlen)
{
	byte* state = cxt->es;
	AES_KEY *ekey = cxt->pt_ekey;

	cxt->ad = (byte*) ad;
	cxt->adlen = adlen;
	cxt->nonce = (byte*) nonce;
	cxt->nlen = nlen;

	int ozp = 0;
	if(adlen < STATE_LEN){
		memcpy(state, ad, adlen);
		memset(state+adlen, 0, STATE_LEN-adlen);
		state[adlen] = 0x80;
		ozp = 1;
	}
	else{
		memcpy(state, ad, STATE_LEN);
	}


	int fix0 = state[0] & 0x80;
	state[0] &= 0x7f;


	AES_encrypt(state, state, ekey);

	if(fix0){
		u32* wd = (u32*) state;
		h(wd[0], wd[1], wd[2], wd[3]);
	}
	else{

	}


	unsigned long long i;
	for(i = 1; i < (unsigned long long)adlen/STATE_LEN; i++){
		xor_block((block*)state, (block*)ad+i);
		AES_encrypt(state, state, ekey);
	}

	unsigned long long lastblocklen = adlen % STATE_LEN;
	if((adlen > STATE_LEN) && lastblocklen){
		xor_bytes(state, ad+i*STATE_LEN, lastblocklen);
		state[lastblocklen] ^= 0x80;
		AES_encrypt(state, state, ekey);
		ozp = 1;
	}


	xor_bytes(state, nonce, nlen);


	if(nlen != STATE_LEN)
		state[nlen] ^= 0x80;


	if(ozp){
		u32* wd = (u32*) state;
		f2(wd[0], wd[1], wd[2], wd[3]);
	}
	else{
		u32* wd = (u32*) state;
		f1(wd[0], wd[1], wd[2], wd[3]);
	}

	memcpy(cxt->ts, state, STATE_LEN);
	AES_encrypt(state, state, ekey);

	return SUCCESS;
}
