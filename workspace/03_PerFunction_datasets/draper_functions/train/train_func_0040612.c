ScanJsonString() {
  ASSERT_EQ('"', c0_);
  Advance();
  LiteralScope literal(this);
  while (c0_ != '"') {

    if (c0_ < 0x20) return Token::ILLEGAL;
    if (c0_ != '\\') {
      AddLiteralCharAdvance();
    } else {
      Advance();
      switch (c0_) {
        case '"':
        case '\\':
        case '/':
          AddLiteralChar(c0_);
          break;
        case 'b':
          AddLiteralChar('\x08');
          break;
        case 'f':
          AddLiteralChar('\x0c');
          break;
        case 'n':
          AddLiteralChar('\x0a');
          break;
        case 'r':
          AddLiteralChar('\x0d');
          break;
        case 't':
          AddLiteralChar('\x09');
          break;
        case 'u': {
          uc32 value = 0;
          for (int i = 0; i < 4; i++) {
            Advance();
            int digit = HexValue(c0_);
            if (digit < 0) {
              return Token::ILLEGAL;
            }
            value = value * 16 + digit;
          }
          AddLiteralChar(value);
          break;
        }
        default:
          return Token::ILLEGAL;
      }
      Advance();
    }
  }
  literal.Complete();
  Advance();
  return Token::STRING;
}
