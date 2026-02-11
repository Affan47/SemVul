data(const DataEvent &event)
{
  const Char *p = event.data.ptr;
  for (size_t len = event.data.len; len > 0; len--, p++) {
    switch (*p) {
    case RE:
      flushRe();
      if (outputState_ == afterStartTag)
	outputRe();
      outputState_ = pendingRe;
      break;
    case '&':
    case '<':
    case '>':
      flushRe();
      outputState_ = other;
      if (parseMode_ == cdataMode)
	os().put(*p);
      else
	numCharRef(*p);
      break;
    default:
      flushRe();
      outputState_ = other;
      if (isSgmlChar(*p))
	os().put(*p);
      else if (parseMode_ == cdataMode) {


	os().put(*p);
      }
      else
	numCharRef(*p);
      break;
    }
  }
}
