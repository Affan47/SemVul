read_image_block (pixma_t * s, uint8_t * header, uint8_t * data)
{
  static const uint8_t cmd[10] =
  { 0xd4, 0x20, 0, 0, 0, 0, 0, IMAGE_BLOCK_SIZE / 256, 4, 0 };
  mp730_t *mp = (mp730_t *) s->subdriver;
  const int hlen = 2 + 4;
  int error, datalen;

  mp->state = state_transfering;
  mp->cb.reslen =
    pixma_cmd_transaction (s, cmd, sizeof (cmd), mp->cb.buf, 512);
  datalen = mp->cb.reslen;
  if (datalen < 0)
    return datalen;

  memcpy (header, mp->cb.buf, hlen);
  if (datalen >= hlen)
    {
      datalen -= hlen;
      memcpy (data, mp->cb.buf + hlen, datalen);
      data += datalen;
      if (mp->cb.reslen == 512)
	{
	  error = pixma_read (s->io, data, IMAGE_BLOCK_SIZE - 512 + hlen);
	  if (error < 0)
	    return error;
	  datalen += error;
	}
    }

  mp->state = state_scanning;
  mp->cb.expected_reslen = 0;
  error = pixma_check_result (&mp->cb);
  if (error < 0)
    return error;
  if (mp->cb.reslen < hlen)
    return PIXMA_EPROTO;
  return datalen;
}
