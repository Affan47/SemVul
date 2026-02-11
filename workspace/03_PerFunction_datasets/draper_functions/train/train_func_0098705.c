indexToLabel(int index, GooString *label)
{
  char buffer[32];
  int i, base, number;
  Interval *interval;
  GooString number_string;

  base = 0;
  interval = NULL;
  for (i = 0; i < intervals.getLength(); i++) {
    interval = (Interval *) intervals.get(i);
    if (base <= index && index < base + interval->length)
      break;
    base += interval->length;
  }

  if (i == intervals.getLength())
    return gFalse;

  number = index - base + interval->first;
  switch (interval->style) {
  case Interval::Arabic:
    snprintf (buffer, sizeof(buffer), "%d", number);
    number_string.append(buffer);
    break;
  case Interval::LowercaseRoman:
    toRoman(number, &number_string, gFalse);
    break;
  case Interval::UppercaseRoman:
    toRoman(number, &number_string, gTrue);
    break;
  case Interval::UppercaseLatin:
  case Interval::LowercaseLatin:
    number = 0;
    break;
  case Interval::None:
    break;
  }

  label->clear();
  label->append(interval->prefix);
  if (label->hasUnicodeMarker()) {
      int i, len;
      char ucs2_char[2];


      len = number_string.getLength ();
      ucs2_char[0] = 0;
      for (i = 0; i < len; ++i) {
	  ucs2_char[1] = number_string.getChar(i);
	  label->append(ucs2_char, 2);
      }
      ucs2_char[1] = 0;
      label->append(ucs2_char, 2);
  } else {
      label->append(&number_string);
  }

  return gTrue;
}
