GetStringSymbol() {
  const int kUseStrictLength = 10;
  const char* kUseStrictChars = "use strict";
  LogSymbol();
  if (scanner_->is_literal_ascii() &&
      scanner_->literal_length() == kUseStrictLength &&
      !scanner_->literal_contains_escapes() &&
      !strncmp(scanner_->literal_ascii_string().start(), kUseStrictChars,
               kUseStrictLength)) {
    return Expression::UseStrictStringLiteral();
  }
  return Expression::StringLiteral();
}
