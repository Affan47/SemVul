ParseBlock(ZoneStringList* labels, bool* ok) {


  Block* result = new Block(labels, 16, false);
  Target target(&this->target_stack_, result);
  Expect(Token::LBRACE, CHECK_OK);
  while (peek() != Token::RBRACE) {
    Statement* stat = ParseStatement(NULL, CHECK_OK);
    if (stat && !stat->IsEmpty()) result->AddStatement(stat);
  }
  Expect(Token::RBRACE, CHECK_OK);
  return result;
}
