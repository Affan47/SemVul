AE_Decrypt(
	      const uint8 *nonce,
		  uint32 nonce_len,
		  const uint8 *ciphertext,
		  uint32 ci_len,
		  const uint8 *header,
		  uint32 h_len,
		  uint32 t_len,
  		  const uint8 *tag,
		  uint8 *plaintext)
{
	uint32 i;
	uint8 loctag[BLOCK];

	if(ADP==Para)
	{
		if(h_len==0){
			memset(TA,0,BLOCK);
		}
		else{
			AFunc(header,h_len);
		}
			DFunc(nonce,nonce_len,ciphertext,ci_len,plaintext);
			xorp(t_len,TE,TA,loctag);
	}
	else if(ADP==Seri)
	{
		if(h_len==0){
			memset(TA,0,BLOCK);
		}
		else{
			AFuncS(header,h_len);
		}
			DFunc(nonce,nonce_len,ciphertext,ci_len,plaintext);
			memcpy(loctag,TE,t_len);
	}

	if(memcmp(loctag,tag,t_len)!=0){
		for(i=0; i<ci_len; i++)plaintext[i] = 0;
		return TAG_UNMATCH;
	}
	return TAG_MATCH;
}
