toloweralias(Alias *ap, logical both) {
  AliasTo *tp;
  char *errstr;
  int erroffset;

  for ( ; ap != NULL; TO_NEXT(ap)) {
    if (headcasematch(ap->from, "REGEXP:"))
      ap->pattern = pcre_compile(ap->from + 7, PCRE_CASELESS | PCRE_DOTALL,
				 (const char **)(&errstr), &erroffset, NULL);

    else if (!headcasematch(ap->from, "REGEXPI:"))

      strtolowerx(ap->from);
    if (both) {
      for (tp = ap->to; tp != NULL; TO_NEXT(tp))
	strtolowerx(tp->string);
    }
  }
}
