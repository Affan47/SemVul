decodeMP3(char *in, int isize)
{
  int len;

  if (in) {
    if (addbuf(gmp, in, isize) == NULL) {
      return MP3_ERR;
    }
  }

  if(mdebug==3)printf("before first decode header\n");

  if (gmp->framesize == 0) {
    if (gmp->bsize < 4) {
      return MP3_NEED_MORE;
    }
  if(mdebug==3)printf("before read_head(gmp)\n");
      read_head(gmp);
  if(mdebug==3)printf("before decode_header(&gmp->fr, gmp->header)\n");
      decode_header(&gmp->fr, gmp->header);

  if(mdebug==3)printf("before gmp->framesize = gmp->fr.framesize\n");
      gmp->framesize = gmp->fr.framesize;
  if(mdebug==3)printf("before Hoffset+=gmp->fr.framesize\n");
      Hoffset+=gmp->fr.framesize;
  }
  if (gmp->fr.framesize > gmp->bsize)
    return MP3_NEED_MORE;
  if(mdebug==3)printf("after return MP3_NEED_MORE\n");

  wordpointer = gmp->bsspace[gmp->bsnum] + 512;
  gmp->bsnum = (gmp->bsnum + 1) & 0x1;
  bitindex = 0;

  if(mdebug==3)printf("before len=0\n");
  len = 0;
  while (len < gmp->framesize) {
    int nlen;
    int blen = gmp->tail->size - gmp->tail->pos;

    if ((gmp->framesize - len) <= blen) {
      nlen = gmp->framesize - len;
    } else {
      nlen = blen;
    }
    memcpy(wordpointer + len, gmp->tail->pnt + gmp->tail->pos, nlen);
    len += nlen;
    gmp->tail->pos += nlen;
    gmp->bsize -= nlen;
    if (gmp->tail->pos == gmp->tail->size) {
      remove_buf(gmp);
    }
  }

  if(mdebug==3)printf("before gmp->fr.error_protection\n");
  if (gmp->fr.error_protection)
    getbits(16);
  do_layer3(&gmp->fr);

  gmp->fsizeold = gmp->framesize;
  gmp->framesize = 0;

  frameNum++;
  return MP3_OK;
}
