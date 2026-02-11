encseq_lua_alphabet(lua_State *L)
{
  GtEncseq **encseq;
  GtAlphabet *alpha;
  encseq = check_encseq(L, 1);
  gt_assert(*encseq);
  alpha = gt_alphabet_ref(gt_encseq_alphabet(*encseq));
  gt_lua_alphabet_push(L, alpha);
  return 1;
}
