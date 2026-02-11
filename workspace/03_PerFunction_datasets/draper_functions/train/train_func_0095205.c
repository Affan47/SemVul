GetIdentifierSymbol() {
  LogSymbol();
  if (scanner_->current_token() == i::Token::FUTURE_RESERVED_WORD) {
    return Identifier::FutureReserved();
  } else if (scanner_->current_token() ==
             i::Token::FUTURE_STRICT_RESERVED_WORD) {
    return Identifier::FutureStrictReserved();
  }
  if (scanner_->is_literal_ascii()) {

    if (scanner_->literal_length() == 4 &&
        !strncmp(scanner_->literal_ascii_string().start(), "eval", 4)) {
      return Identifier::Eval();
    }
    if (scanner_->literal_length() == 9 &&
        !strncmp(scanner_->literal_ascii_string().start(), "arguments", 9)) {
      return Identifier::Arguments();
    }
  }
  return Identifier::Default();
}
