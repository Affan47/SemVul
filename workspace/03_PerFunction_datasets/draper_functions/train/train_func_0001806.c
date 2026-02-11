luaD_travstack (int (*fn)(TObject *))
{
  StkId i;
  for (i = (L->stack.top-1)-L->stack.stack; i>=0; i--)
    fn(L->stack.stack+i);
}
