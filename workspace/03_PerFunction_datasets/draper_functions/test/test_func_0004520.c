lj_tab_getinth(GCtab *t, int32_t key)
{
  TValue k;
  Node *n;
  k.n = (lua_Number)key;
  n = hashnum(t, &k);
  do {
    if (tvisnum(&n->key) && n->key.n == k.n)
      return &n->val;
  } while ((n = nextnode(n)));
  return NULL;
}
