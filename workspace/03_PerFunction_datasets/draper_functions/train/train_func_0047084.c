ftencode_init(struct ftencode *enc, int flags)
{

  bzero(enc, sizeof (struct ftencode));

  enc->flags = flags;

  if (enc->flags & FT_ENC_FLAGS_IPHDR)
    enc->buf_enc = (char*)&enc->buf + FT_ENC_IPHDR_LEN;
  else
    enc->buf_enc = (char*)&enc->buf;

}
