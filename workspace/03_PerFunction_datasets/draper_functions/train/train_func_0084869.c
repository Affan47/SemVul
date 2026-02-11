AsssString (
    Obj                 list,
    Obj                 poss,
    Obj                 vals )
{
  Int i, len = LEN_LIST(poss);
  for (i = 1; i <= len; i++) {
    ASS_LIST(list, INT_INTOBJ(ELM_LIST(poss, i)), ELM_LIST(vals, i));
  }
}
