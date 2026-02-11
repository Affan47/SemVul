fixQuotes(UnicodeString& s) {
  QuoteState state = OUTSIDE;
  int32_t len = s.length();
  int32_t dest = 0;
  for (int32_t i = 0; i < len; ++i) {
    UChar ch = s.charAt(i);
    if (ch == u_apos) {
      if (state == INSIDE_EMPTY) {
        s.setCharAt(dest, ch);
        ++dest;
      }
    } else {
      s.setCharAt(dest, ch);
      ++dest;
    }


    switch (state) {
      case OUTSIDE:
        state = ch == u_apos ? INSIDE_EMPTY : OUTSIDE;
        break;
      case INSIDE_EMPTY:
      case INSIDE_FULL:
        state = ch == u_apos ? OUTSIDE : INSIDE_FULL;
        break;
      default:
        break;
    }
  }
  s.truncate(dest);
}
