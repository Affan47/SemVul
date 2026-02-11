StackReload(cs)
ChimeraStack cs;
{
  URLInfo *u;
  ChimeraRequest *wr;

  if ((u = GListGetHead(cs->urls)) == NULL) return;
  wr = RequestCreate(cs->wc->cres, u->url, NULL);
  RequestReload(wr, true);
  StackOp(cs, wr, StackReloadAction);

  return;
}
