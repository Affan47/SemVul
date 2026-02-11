yyDo(GREG *G, yyaction action, int begin, int end)
{
  while (G->thunkpos >= G->thunkslen)
    {
      G->thunkslen *= 2;
      G->thunks= YY_REALLOC(G->thunks, sizeof(yythunk) * G->thunkslen, G->data);
    }
  G->thunks[G->thunkpos].begin=  begin;
  G->thunks[G->thunkpos].end=    end;
  G->thunks[G->thunkpos].action= action;
  ++G->thunkpos;
}
