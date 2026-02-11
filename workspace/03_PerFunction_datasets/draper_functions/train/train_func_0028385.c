_gcry_cipher_ccm_decrypt (gcry_cipher_hd_t c, unsigned char *outbuf,
                          size_t outbuflen, const unsigned char *inbuf,
                          size_t inbuflen)
{
  gcry_err_code_t err;
  unsigned int burn;

  if (outbuflen < inbuflen)
    return GPG_ERR_BUFFER_TOO_SHORT;
  if (!c->u_mode.ccm.nonce || c->marks.tag || !c->u_mode.ccm.lengths ||
      c->u_mode.ccm.aadlen > 0)
    return GPG_ERR_INV_STATE;
  if (inbuflen > c->u_mode.ccm.encryptlen)
    return GPG_ERR_INV_LENGTH;

  err = _gcry_cipher_ctr_encrypt (c, outbuf, outbuflen, inbuf, inbuflen);
  if (err)
    return err;

  c->u_mode.ccm.encryptlen -= inbuflen;
  burn = do_cbc_mac (c, outbuf, inbuflen, 0);
  if (burn)
    _gcry_burn_stack (burn + sizeof(void *) * 5);

  return err;
}
