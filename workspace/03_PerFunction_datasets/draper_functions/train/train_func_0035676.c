ae_encrypt(ae_cxt* cxt, byte* pt, unsigned long long mlen, byte* ct, byte* tag, unsigned long long tlen, int enc_dec)
{
	cxt->pt = pt;
	cxt->ptlen = mlen;
	cxt->ct = ct;
	cxt->ctlen = mlen;
	cxt->tag = tag;
	cxt->tlen = tlen;

	byte* es = cxt->es;
	byte* ts = cxt->ts;
	AES_KEY *ekey = cxt->pt_ekey;


	unsigned long long pc = 0;
	while((pc + STATE_LEN) < mlen){
		if(enc_dec == ENC){
			xor_bytes(es, pt+pc, STATE_LEN);
			pstate2("After xoring message block:", es);
			memcpy(ct+pc, es, STATE_LEN);
		}
		else{
			xor_bytes2(pt+pc, ct+pc, es, STATE_LEN);
			pstate2("After xoring ciphertext block:", es);
			memcpy(es, ct+pc, STATE_LEN);
		}
		xor_bytes(ts, es, STATE_LEN);
		pstate2("tag state:", ts);
		pstate2("Enc:", NULL);
		AES_encrypt(ts, ts, ekey);

		es[0] |= 0x80;
		pstate2("After applying fix1:", es);
		pstate2("Enc:", NULL);
		AES_encrypt(es, es, ekey);
		pc += STATE_LEN;
	}


	unsigned long long lastblocklen = mlen - pc;

	if(lastblocklen > 0){
		if(enc_dec == ENC){
			xor_bytes(es, pt+pc, lastblocklen);
			pstate2("After xoring last partial message block:", es);
			memcpy(ct+pc, es, lastblocklen);
		}
		else{
			xor_bytes2(pt+pc, ct+pc, es, lastblocklen);
			pstate2("After xoring last partial ciphertext block:", es);
			memcpy(es, ct+pc, lastblocklen);
		}
		xor_bytes(ts, es, lastblocklen);
		pstate2("tag state:", ts);
		pstate2("Enc:", NULL);
		AES_encrypt(ts, ts, ekey);
	}

	unsigned long long t_adlen = mlen;
	unsigned long long i;
	for(i = 0; i < sizeof(unsigned long long); i++) {
		ts[STATE_LEN-1-i] ^= t_adlen & 0xff;
		t_adlen >>= 8;
	}
	pstate2("After xoring the legnth of message:", ts);
	g(ts);
	pstate2("After applying g:", ts);
	pstate2("Enc:", NULL);
	AES_encrypt(ts, ts, ekey);

	memcpy(tag, ts, tlen);
	return SUCCESS;
}
