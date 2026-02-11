inflate_buff(const char* buff, const size_t size, char** out_buff)
{
  int res = Z_OK;
  z_stream strm;
  char out[DEFLATE_BUFF_SIZE];
  char* cout = NULL;
  gbuint32 bytes = 0;
  gbuint32 have;

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;

  res = inflateInit(&strm);
  if (res != Z_OK) {
    return res;
  }

  strm.avail_in = size;
  strm.next_in = (Bytef*)buff;

  do {
    strm.avail_out = DEFLATE_BUFF_SIZE;
    strm.next_out = (Bytef*)out;
    res = inflate(&strm, Z_NO_FLUSH);

    switch (res) {
    case Z_NEED_DICT:
      res = Z_DATA_ERROR;
    case Z_DATA_ERROR:
    case Z_MEM_ERROR:
      (void)inflateEnd(&strm);
      return res;
    }
    have = DEFLATE_BUFF_SIZE - strm.avail_out;
    if (have > 0) {
      cout = (char*) xrealloc(cout, bytes + have);
      memcpy(cout+bytes, out, have);
      bytes+=have;
    }
  } while (strm.avail_out == 0);

  *out_buff = cout;
  return res;
}
