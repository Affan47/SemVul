reduce_grammar (void)
{
  bool reduced;


  N = bitset_create (nvars, BITSET_FIXED);
  P =  bitset_create (nrules, BITSET_FIXED);
  V = bitset_create (nsyms, BITSET_FIXED);
  V1 = bitset_create (nsyms, BITSET_FIXED);

  useless_nonterminals ();
  inaccessable_symbols ();

  reduced = (nuseless_nonterminals + nuseless_productions > 0);
  if (!reduced)
    return;

  reduce_print ();

  if (!bitset_test (N, accept->number - ntokens))
    complain (&startsymbol_location, fatal,
              _("start symbol %s does not derive any sentence"),
              startsymbol->tag);


  if (nuseless_nonterminals > 0)
    nonterminals_reduce ();
  if (nuseless_productions > 0)
    reduce_grammar_tables ();

  if (trace_flag & trace_grammar)
    {
      grammar_dump (stderr, "Reduced Grammar");

      fprintf (stderr, "reduced %s defines %d terminals, %d nonterminals"
               ", and %d productions.\n",
               grammar_file, ntokens, nvars, nrules);
    }
}
