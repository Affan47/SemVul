ParseJsonArray() {
  ZoneScope zone_scope(DELETE_ON_EXIT);
  ZoneList<Handle<Object> > elements(4);

  Token::Value token = scanner_.peek();
  if (token == Token::RBRACK) {
    scanner_.Next();
  } else {
    if (StackLimitCheck().HasOverflowed()) {
      stack_overflow_ = true;
      return Handle<Object>::null();
    }
    do {
      Handle<Object> element = ParseJsonValue();
      if (element.is_null()) return Handle<Object>::null();
      elements.Add(element);
      token = scanner_.Next();
    } while (token == Token::COMMA);
    if (token != Token::RBRACK) {
      return ReportUnexpectedToken();
    }
  }


  Handle<FixedArray> fast_elements =
      Factory::NewFixedArray(elements.length());

  for (int i = 0, n = elements.length(); i < n; i++) {
    fast_elements->set(i, *elements[i]);
  }

  return Factory::NewJSArrayWithElements(fast_elements);
}
