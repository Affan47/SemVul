crypto_aead_decrypt(
   unsigned char *m,        unsigned long long *mlen,
   unsigned char *nsec,
   const unsigned char *c,  unsigned long long clen,
   const unsigned char *ad, unsigned long long adlen,
   const unsigned char *npub,
   const unsigned char *k
)
{
   static unsigned char d_k[16], d_IVa[16], d_IVb[16];
   unsigned char         icv[16], b1[16], b2[16];
   int                   i;

   if ( k!=0 ) {
      memcpy( d_k, k, 16 ); gen_ivs( d_IVa, d_IVb, npub, d_k );
      }

   gen_icv( icv, npub, *mlen=clen-16, adlen, d_IVa, d_IVb );
   gtag_ad( d_IVa, ad, adlen, d_k, icv );

   for ( ; clen>16; m+=16, c+=16 ) {
      decppae( b1, d_IVa, d_IVb, c, d_k );
      if ( (clen-=16) < 16 ) {
         for ( i=0; i<16; i++ ) b1[i] ^= (b2[i] = icv[((16-clen)+i)%16]);
         for ( i=clen; i<16; i++ ) if ( b1[i] ) return -1;
         for ( i=0; i<16; i++ ) icv[i] = b2[i];
      }
      memcpy( m, b1, (clen<16)? clen : 16 );
   }

   encppae( b1, d_IVa, d_IVb, icv, d_k );
   if ( memcmp( b1+(16-clen), c, clen ) ) return -1;

   return 0;
}
