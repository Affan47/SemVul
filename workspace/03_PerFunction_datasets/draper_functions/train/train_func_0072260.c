bufGetBuf (gdIOCtxPtr ctx, void* buf, int len) {
  bufIOCtxPtr bctx = (bufIOCtxPtr) ctx;
  int remain,rlen;

  remain = bctx->length - bctx->pos;
  if (remain >= len) {
    rlen = len;
  } else {
    if (remain <= 0) return EOF;
    rlen = remain;
  }
  memcpy(buf,(void*)(bctx->data + bctx->pos),rlen);
  bctx->pos += rlen;
  return rlen;
}
