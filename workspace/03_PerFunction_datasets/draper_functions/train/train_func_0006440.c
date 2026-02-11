mgrib_ctxdelete( mgcontext *ctx )
{


  if(ctx->devno != MGD_RIB) {
    mgcontext *was = _mgc;
    mgctxselect(ctx);
    mgctxdelete(ctx);
    if(was != ctx) {
      mgctxselect(was);
    }
  } else {
    if(((mgribcontext *)ctx)->shadepath) {
      free(((mgribcontext *)ctx)->shadepath);
    }
    if (_mgribc->tx) {
      OOGLFree(_mgribc->tx);
    }
    mrti_delete(&_mgribc->worldbuf);
    mrti_delete(&_mgribc->txbuf);
    mg_ctxdelete(ctx);
    if(ctx == _mgc)
      _mgc = NULL;
  }
}
