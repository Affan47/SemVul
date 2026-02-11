udf_checktag(const udf_tag_t *p_tag, udf_Uint16_t tag_id)
{
  uint8_t *itag;
  uint8_t i;
  uint8_t cksum = 0;

  itag = (uint8_t *)p_tag;

  if (p_tag->id != tag_id)
    return -1;

  for (i = 0; i < 15; i++)
    cksum = cksum + itag[i];
  cksum = cksum - itag[4];

  if (cksum == p_tag->cksum)
    return 0;

  return -1;
}
