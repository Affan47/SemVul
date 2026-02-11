RequestAddContent(wr, content)
ChimeraRequest *wr;
char *content;
{
  if (wr->contents == NULL) wr->contents = GListCreateX(wr->mp);
  GListAddTail(wr->contents, MPStrDup(wr->mp, content));
  return;
}
