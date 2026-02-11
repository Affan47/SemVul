lp_seq (lua_State *L) {
  TTree *tree1 = getpatt(L, 1, NULL);
  TTree *tree2 = getpatt(L, 2, NULL);
  if (tree1->tag == TFalse || tree2->tag == TTrue)
    lua_pushvalue(L, 1);
  else if (tree1->tag == TTrue)
    lua_pushvalue(L, 2);
  else
    newroot2sib(L, TSeq);
  return 1;
}
