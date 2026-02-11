closure (item_number const *core, size_t n)
{

  size_t c;


  rule_number ruleno;

  bitset_iterator iter;

  if (trace_flag & trace_sets)
    print_closure ("input", core, n);

  bitset_zero (ruleset);

  for (c = 0; c < n; ++c)
    if (ISVAR (ritem[core[c]]))
      bitset_or (ruleset, ruleset, FDERIVES (ritem[core[c]]));


  nitemset = 0;
  c = 0;
  BITSET_FOR_EACH (iter, ruleset, ruleno, 0)
    {
      item_number itemno = rules[ruleno].rhs - ritem;
      while (c < n && core[c] < itemno)
        {
          itemset[nitemset] = core[c];
          nitemset++;
          c++;
        }
      itemset[nitemset] = itemno;
      nitemset++;
    };

  while (c < n)
    {
      itemset[nitemset] = core[c];
      nitemset++;
      c++;
    }

  if (trace_flag & trace_sets)
    print_closure ("output", itemset, nitemset);
}
