mgrib_flushbuffer()
{
  TokenBuffer *wbuf = &_mgribc->worldbuf;
  size_t size;

  if(!_mgribc->rib) {
    if (mgrib_ctxset(MG_RIBDISPLAYNAME, DEFAULT_RIB_FILE, MG_END) == -1) {
      return;
    }
  }
  if (_mgribc->tx) {
    TokenBuffer *txbuf = &_mgribc->txbuf;

    size = (size_t)wbuf->tkb_worldptr - (size_t)wbuf->tkb_buffer;
    if (size && fwrite(wbuf->tkb_buffer, size, 1, _mgribc->rib) != 1) {
      OOGLError(1, "Error flushing RIB tokenbuffer (prologue)");
    }
    mrti_makecurrent(txbuf);
    mrti(mr_nl, mr_nl, mr_NULL);
    size = (size_t)txbuf->tkb_ptr - (size_t)txbuf->tkb_buffer;
    if (size && fwrite(txbuf->tkb_buffer, size, 1, _mgribc->rib) != 1) {
      OOGLError(1, "Error flushing RIB tokenbuffer (textures)");
    }
    size = (size_t)wbuf->tkb_ptr - (size_t)wbuf->tkb_worldptr;
    if (size && fwrite(wbuf->tkb_worldptr, size, 1, _mgribc->rib) != 1) {
      OOGLError(1, "Error flushing RIB tokenbuffer (world)");
    }
    mrti_reset();
  } else {
    size = (size_t)wbuf->tkb_ptr - (size_t)wbuf->tkb_buffer;
    if (size && fwrite(wbuf->tkb_buffer, size, 1, _mgribc->rib) != 1) {
      OOGLError(1, "Error flushing RIB tokenbuffer");
    }
  }
  fflush(_mgribc->rib);
  mrti_makecurrent(wbuf);
  mrti_reset();
}
