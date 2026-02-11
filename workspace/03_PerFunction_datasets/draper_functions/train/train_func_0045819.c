_gcry_cipher_decrypt (gcry_cipher_hd_t h, void *out, size_t outsize,
                      const void *in, size_t inlen)
{
  if (!in)
    {
      in = out;
      inlen = outsize;
    }

  return cipher_decrypt (h, out, outsize, in, inlen);
}
