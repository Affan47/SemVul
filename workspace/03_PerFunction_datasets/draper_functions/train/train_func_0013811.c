create_aligner(ElementT *e, RouterT *, ErrorHandler *errh)
{
  int m;
  ContextErrorHandler cerrh(errh, "While analyzing alignment for '" + e->declaration() + "':");
  if (cp_va_parse(e->configuration(), &cerrh,
		  cpInteger, "amount to strip", &m,
		  cpEnd) < 0)
    return default_aligner();
  return new ShifterAligner(m);
}
