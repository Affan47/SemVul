input_bit(ac_decoder *acd)
  {
  uint32_t iB;

  if(!acd->bits_to_go)
    {
    if(acd->indexBuf == acd->maxBuf)
      {
      acd->maxBuf   = fread(acd->buf, 0x1, CBUF_SIZE, acd->fp);
      acd->indexBuf = 0x0;
      }
    acd->buffer     = acd->buf[acd->indexBuf++];
    acd->bits_to_go = 8;
    }

  iB = acd->buffer & 0x1, acd->buffer >>= 0x1, --acd->bits_to_go;

  return iB;
  }
