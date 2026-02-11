yyCommit(GREG *G)
{
  if ((G->limit -= G->pos))
    {
      memmove(G->buf, G->buf + G->pos, G->limit);
    }
  G->begin -= G->pos;
  G->end -= G->pos;
  G->pos= G->thunkpos= 0;
}
