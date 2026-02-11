rsa_verify(unsigned char *M,int mlen,unsigned char *S,int slen,public_key_mpz *pu) {

	int k = mpz_sizeinbase(pu->mod,2)/8;
	size_t size = 0;
	int emlen = k;
	uchar *EM,*EM1;
	uchar *C;

	mpz_t m;mpz_init(m);
	mpz_t s;mpz_init(s);
	mpz_t c;mpz_init(c);

	if(slen!=k){
		printf("Signed msg length error \n");
		return 0;
	}
	mpz_import(s,slen,1,1,0,0,S);
	if(RSA_POWM(s,pu->mod,pu->pub_exp,&c) == 0)
		return 0;
	EM = mpz_export(NULL,&size,1,1,0,0,c);

	EM1 = EMSA_PKCS1_v1_5_ENCODE(M,mlen,emlen);

	if(size==emlen-1 && (memcmp(EM,EM1+1,size) == 0))
		return 1;
	else
		return 0;
}
