zlib_compress (void *src, uint32_t srcLen, void *dest, uint32_t destLen,
    int level, int strat)
{
  if (strat == Z_USE_7Z) {

    if (destLen < 6)
      return 0;

    unsigned int outSize = destLen - 6;
    unsigned char *destPtr = (unsigned char *) dest;

    *(uint16_t *) destPtr = 0xDA78;
    destPtr += 2;

    int passes = 1, fastbytes = 64;

    switch (level) {
      case 1:
	passes = 1;
	fastbytes = 64;
	break;
      case 2:
	passes = 3;
	fastbytes = 128;
	break;
      case 3:
	passes = 5;
	fastbytes = 255;
	break;
      case 4:
	passes = 15;
	fastbytes = 255;
	break;
    }

    if (!compress_deflate_7z ((unsigned char *) src, srcLen, destPtr, &outSize,
	    passes, fastbytes))
      return 0;

    if (outSize + 6 > destLen)
      return 0;

    uLong adler = adler32 (adler32 (0L, Z_NULL, 0), (Bytef *) src, srcLen);

#define ENDIAN_SWAP_32(x) (((x) & 0xFF) << 24 | ((x) & 0xFF00) << 8 | ((x) & 0xFF0000) >> 8 | ((x) & 0xFF000000) >> 24)
    *(uint32_t *) (destPtr + outSize) = ENDIAN_SWAP_32 (adler);

    return outSize + 6;
  } else {

    z_stream s;

    memset (&s, 0, sizeof (s));
    if (deflateInit2 (&s, level, Z_DEFLATED, 15, 8, strat))
      return 0;

    s.next_in = (Bytef *) src;
    s.avail_in = srcLen;
    s.next_out = (Bytef *) dest;
    s.avail_out = destLen;

    if (deflate (&s, Z_FINISH) < 0)
      return 0;

    deflateEnd (&s);
    return s.total_out;
  }
}
