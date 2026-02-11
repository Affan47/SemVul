load(SgmlParser &specParser,
				 const CharsetInfo &charset,
				 const StringC &id,
				 Vector<Part *> &parts)
{
  parser_ = &specParser;
  charset_ = &charset;
  Doc *doc = findDoc(StringC());

  doc->load(*this);
  Part *tem;
  if (id.size() == 0)
    tem = doc->resolveFirstPart(*this);
  else {
    StringC normId(id);
    ConstPtr<Syntax> syn = parser_->instanceSyntax();
    if (!syn.isNull())
      syn->generalSubstTable()->subst(normId);
    tem = doc->refPart(normId)->resolve(*this);
  }
  resolveParts(tem, parts);
}
