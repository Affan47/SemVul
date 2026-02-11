Copy_Term(WamWord *dst_adr, WamWord *src_adr)
{
  WamWord *qtop, *base;
  WamWord *p;


  static WamWord *fix_bug;

  base_copy = dst_adr++;

  base = top_vars = vars;

  fix_bug = dst_adr;
  Copy_Term_Rec(base_copy, src_adr, &fix_bug);


  qtop = top_vars;
  while (qtop != base)
    {
      p = (WamWord *) (*--qtop);
      *p = *--qtop;
    }
}
