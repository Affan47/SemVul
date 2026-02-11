labelToIndex(GooString *label, int *index)
{
  Interval *interval;
  char *str = label->getCString(), *end;
  int prefixLength;
  int i, number;

  for (i = 0; i < intervals.getLength(); i++) {
    interval = (Interval *) intervals.get(i);
    const int base = interval->base;
    prefixLength = interval->prefix->getLength();
    if (label->cmpN(interval->prefix, prefixLength) != 0)
      continue;

    switch (interval->style) {
    case Interval::Arabic:
      number = strtol(str + prefixLength, &end, 10);
      if (*end == '\0' && number - interval->first < interval->length) {
	*index = base + number - interval->first;
	return gTrue;
      }
      break;
    case Interval::LowercaseRoman:
    case Interval::UppercaseRoman:
      number = fromRoman(str + prefixLength);
      if (number >= 0 && number - interval->first < interval->length) {
	*index = base + number - interval->first;
	return gTrue;
      }
      break;
    case Interval::UppercaseLatin:
    case Interval::LowercaseLatin:
      number = fromLatin(str + prefixLength);
      if (number >= 0 && number - interval->first < interval->length) {
	*index = base + number - interval->first;
	return gTrue;
      }
      break;
    case Interval::None:
      break;
    }
  }

  return gFalse;
}
