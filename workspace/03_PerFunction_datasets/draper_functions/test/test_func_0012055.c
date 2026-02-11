ParseJsonObject() {
  Handle<JSFunction> object_constructor(
      Top::global_context()->object_function());
  Handle<JSObject> json_object = Factory::NewJSObject(object_constructor);
  if (scanner_.peek() == Token::RBRACE) {
    scanner_.Next();
  } else {
    if (StackLimitCheck().HasOverflowed()) {
      stack_overflow_ = true;
      return Handle<Object>::null();
    }
    do {
      if (scanner_.Next() != Token::STRING) {
        return ReportUnexpectedToken();
      }
      Handle<String> key = GetString();
      if (scanner_.Next() != Token::COLON) {
        return ReportUnexpectedToken();
      }
      Handle<Object> value = ParseJsonValue();
      if (value.is_null()) return Handle<Object>::null();
      uint32_t index;
      if (key->AsArrayIndex(&index)) {
        SetOwnElement(json_object, index, value);
      } else if (key->Equals(Heap::Proto_symbol())) {


        SetPrototype(json_object, value);
      } else {
        SetLocalPropertyIgnoreAttributes(json_object, key, value, NONE);
      }
    } while (scanner_.Next() == Token::COMMA);
    if (scanner_.current_token() != Token::RBRACE) {
      return ReportUnexpectedToken();
    }
  }
  return json_object;
}
