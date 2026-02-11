aes_set_iv(aes_cnt_cipher_t *cipher, const char *iv)
{
#ifdef USING_COUNTER_VARS
  cipher->counter3 = ntohl(get_uint32(iv));
  cipher->counter2 = ntohl(get_uint32(iv+4));
  cipher->counter1 = ntohl(get_uint32(iv+8));
  cipher->counter0 = ntohl(get_uint32(iv+12));
#endif
  cipher->pos = 0;
  memcpy(cipher->ctr_buf.buf, iv, 16);

#ifdef CAN_USE_OPENSSL_CTR
  if (!should_use_openssl_CTR)
#endif
    _aes_fill_buf(cipher);
}
