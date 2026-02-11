GWEN_FastBuffer_ReadLineToBuffer(GWEN_FAST_BUFFER *fb, GWEN_BUFFER *buf) {
  int lineComplete=0;
  int hadSome=0;

  while (!lineComplete) {
    int bytes;
    int copied=0;
    uint8_t *p;

    if (fb->bufferReadPos>=fb->bufferWritePos) {
      int rv;

      rv=GWEN_SyncIo_Read(fb->io, fb->buffer, fb->bufferSize);
      if (rv<0) {
	if (rv==GWEN_ERROR_EOF && hadSome) {

	  return 0;
	}
	DBG_INFO(GWEN_LOGDOMAIN, "here (%d)", rv);
	return rv;
      }
      else if (rv==0) {
        DBG_DEBUG(GWEN_LOGDOMAIN, "EOF met");
        if (!hadSome)
          return GWEN_ERROR_EOF;
        lineComplete=1;

      }
      else {
	fb->bufferWritePos=rv;
	fb->bufferReadPos=0;
      }
    }

    bytes=fb->bufferWritePos-fb->bufferReadPos;
    p=fb->buffer+fb->bufferReadPos;
    while(bytes) {
      uint8_t c;

      hadSome=1;

      c=fb->buffer[fb->bufferReadPos++];
      fb->bytesRead++;
      bytes--;
      if (c==10) {
	lineComplete=1;

	break;
      }
      else if (c==13) {
	break;
      }
      else {
	copied++;
      }
    }

    if (copied)
      GWEN_Buffer_AppendBytes(buf, (const char*)p, copied);
  }

  return 0;
}
