AIO_OfxXmlCtx_FreeData(void *bp, void *p) {
  AIO_OFX_XMLCTX *xctx;
  AIO_OFX_GROUP *g;

  xctx=(AIO_OFX_XMLCTX*)p;

  g=xctx->currentGroup;
  while (g) {
    AIO_OFX_GROUP *gParent;

    gParent=AIO_OfxGroup_GetParent(g);
    AIO_OfxGroup_free(g);
    g=gParent;
  }

  free(xctx->resultSeverity);
  free(xctx->currentTagName);

  free(xctx->charset);

  GWEN_FREE_OBJECT(xctx);
}
