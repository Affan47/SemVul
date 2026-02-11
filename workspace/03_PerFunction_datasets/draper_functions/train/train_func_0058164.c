tokenize(Char space, Text &text) const
{
  TextIter iter(*this);
  TextItem::Type type;
  const Char *p;
  size_t n;
  const Location *loc;
  while (iter.next(type, p, n, loc)) {
    switch (type) {
    case TextItem::data:
      text.addCharsTokenize(p, n, *loc, space);
      break;
    case TextItem::sdata:
    case TextItem::cdata:
      {
	text.addEntityStart(*loc);
	text.addCharsTokenize(p, n, *loc, space);
	Location tem(*loc);
	tem += n;
	text.addEntityEnd(tem);
      }
      break;
    case TextItem::ignore:
      text.ignoreChar(*p, *loc);
      break;
    default:
      text.addSimple(type, *loc);
      break;
    }
  }
  if (text.size() > 0 && text.lastChar() == space)
    text.ignoreLastChar();
}
