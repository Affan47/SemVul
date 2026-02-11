literalSign() const {
  if (Type != kTokenLiteral)
    return -1;
  return (LiteralSign ? 1 : 0);
}
