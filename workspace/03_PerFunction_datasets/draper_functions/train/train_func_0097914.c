MR_max_height_of_tree(Tree *t)
#else
int MR_max_height_of_tree(t)
  Tree  *t;
#endif
{
  int       h;
  int       height=0;
  Tree      *u;

  if (t == NULL) return 0;

  require (t->token != ALT && t->token != EpToken,"MR_max_height_of_tree ALT or EpToken");

  for (u=t; u != NULL; u=u->right) {
    h=MR_max_height_of_tree(u->down)+1;
    if (h > height) height=h;
  };
  return height;
}
