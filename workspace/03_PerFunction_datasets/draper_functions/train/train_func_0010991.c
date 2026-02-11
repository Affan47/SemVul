makeSemantics(const TokenizedAttributeValue &value,
				  AttributeContext &context,
				  const StringC &,
				  unsigned &nIdrefs,
				  unsigned &) const
{
  size_t nTokens = value.nTokens();
  nIdrefs += nTokens;
  for (size_t i = 0; i < nTokens; i++)
    context.noteIdref(value.token(i), value.tokenLocation(i));
  return 0;
}
