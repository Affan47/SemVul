cmac_read (gcry_mac_hd_t h, unsigned char *outbuf, size_t * outlen)
{
  if (*outlen > h->u.cmac.blklen)
    *outlen = h->u.cmac.blklen;
  return _gcry_cipher_cmac_get_tag (h->u.cmac.ctx, outbuf, *outlen);
}
