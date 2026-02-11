do_ecb_encrypt (gcry_cipher_hd_t c,
                unsigned char *outbuf, unsigned int outbuflen,
                const unsigned char *inbuf, unsigned int inbuflen)
{
  unsigned int blocksize = c->cipher->blocksize;
  unsigned int n, nblocks;

  if (outbuflen < inbuflen)
    return GPG_ERR_BUFFER_TOO_SHORT;
  if ((inbuflen % blocksize))
    return GPG_ERR_INV_LENGTH;

  nblocks = inbuflen / c->cipher->blocksize;

  for (n=0; n < nblocks; n++ )
    {
      c->cipher->encrypt (&c->context.c, outbuf, (byte*)inbuf);
      inbuf  += blocksize;
      outbuf += blocksize;
    }
  return 0;
}
