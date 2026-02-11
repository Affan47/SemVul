crypto_aead_decrypt(
    unsigned char *m, 		unsigned long long *mlen,
    unsigned char *nsec,
    const unsigned char *c, 	unsigned long long clen,
    const unsigned char *ad,	unsigned long long adlen,
    const unsigned char *npub,
    const unsigned char *k
    )
{
  unsigned char key[CRYPTO_KEYBYTES];
  unsigned char ta[OTR_BLOCKBYTES];
  unsigned char te[OTR_BLOCKBYTES];
  unsigned char l[OTR_BLOCKBYTES];
  unsigned char delta[OTR_BLOCKBYTES];
  unsigned char sigma[OTR_BLOCKBYTES];
  unsigned char buf[2*OTR_BLOCKBYTES];
  unsigned long long i;

  if(clen < CRYPTO_ABYTES) return -1;
  if((clen-OTR_TAGBYTES) & (OTR_BLOCKBYTES-1)) return -1;

  *mlen = 0;

  for(i=0;i<CRYPTO_KEYBYTES;i++)
    key[i] = k[i];


  otr_process_ad(ta, ad, adlen, key);


  for(i=0;i<OTR_BLOCKBYTES;i++)
    sigma[i] = 0;
  padblock(delta,npub,CRYPTO_NPUBBYTES);
  encrypt_block(delta,delta,key);
  mulx(l,delta);
  mulx(l,l);


  while(clen-OTR_TAGBYTES >= 2*OTR_BLOCKBYTES)
  {
    feistelback(m, c, l, delta, key);
    xor_block(sigma, sigma, m+OTR_BLOCKBYTES);
    mulx(l,l);

    m     += 2*OTR_BLOCKBYTES;
    c     += 2*OTR_BLOCKBYTES;
    clen  -= 2*OTR_BLOCKBYTES;
    *mlen += 2*OTR_BLOCKBYTES;
  }

  if(clen-OTR_TAGBYTES)
  {
    encrypt_block(buf, l, key);
    xor_block(m,c,buf);
    xor_block(sigma, sigma, m);

    *mlen += OTR_BLOCKBYTES;
    m     += OTR_BLOCKBYTES;
    c     += OTR_BLOCKBYTES;
  }
  else
  {
    xor_block(l, l, delta);
  }


  mulxp1(l,l);
  xor_block(te, sigma, l);
  xor_block(te, te, delta);
  encrypt_block(te, te, key);

  for(i=0;i<OTR_TAGBYTES;i++)
    te[i] ^= ta[i];


  while((*mlen) > 0)
  {
    (*mlen)--;
    m--;
    if((*m) == 0x80) break;
    if((*m) != 0x00) return -1;
  }

  zerobytes(key, CRYPTO_KEYBYTES);

  return crypto_verify_32(te, c);
}
