processtEXt (struct EXTRACTOR_ExtractContext *ec,
             uint32_t length)
{
  void *ptr;
  unsigned char *data;
  char *keyword;
  size_t off;
  unsigned int i;
  int ret;

  if (length != ec->read (ec->cls, &ptr, length))
    return 1;
  data = ptr;
  off = stnlen ((char*) data, length) + 1;
  if (off >= length)
    return 0;
  if (NULL == (keyword = EXTRACTOR_common_convert_to_utf8 ((char*) &data[off],
							   length - off,
							   "ISO-8859-1")))
    return 0;
  ret = 0;
  for (i = 0; NULL != tagmap[i].name; i++)
    if (0 == strcmp (tagmap[i].name, (char*) data))
      {
	ADDF (tagmap[i].type, keyword);
	return 0;
      }
  ADDF (EXTRACTOR_METATYPE_KEYWORDS, keyword);
FINISH:
  return ret;
}
