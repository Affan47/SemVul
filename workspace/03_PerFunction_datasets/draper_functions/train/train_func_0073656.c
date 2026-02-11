sdParamLiteral(const SdText &text)
{
  const StringC &delim = syntax_->delimGeneral(text.lita()
					       ? Syntax::dLITA
					       : Syntax::dLIT);
  os() << delim;
  SdTextIter iter(text);
  const SyntaxChar *p;
  size_t n;
  Location loc;
  while (iter.next(p, n, loc)) {
    const Markup *markupPtr;
    if (n == 1 && loc.origin()->isNumericCharRef(markupPtr)) {
      if (markupPtr)
	outputMarkup(loc.origin()->parent(), *markupPtr);
    }
    else if (n > 0) {
      Char c = Char(*p);
      withNamedCharRef(&c, 1, loc);
      for (++p, --n; n > 0; ++p, --n)
	os().put(Char(*p));
    }
  }
  os() << delim;
}
