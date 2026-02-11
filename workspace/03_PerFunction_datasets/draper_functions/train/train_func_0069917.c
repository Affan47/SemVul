setvbuf_unlocked(FILE *stream, char *buf, int flags, size_t size) {
  if (buf) {
    if (!(stream->flags&STATICBUF)) free(stream->buf);
    stream->buf=buf;
  }
  else {
    char *tmp;
    if (!size) {
      return set_flags(stream,flags);
    }
    if (!(tmp=malloc(size))) return -1;
    if (!(stream->flags&STATICBUF)) free(stream->buf);
    stream->buf=tmp;
  }
  stream->flags &= ~STATICBUF;
  stream->buflen=size;
  stream->bm=stream->bs=0;
  return set_flags(stream,flags);
}
