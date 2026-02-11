tokenRecover(unsigned allowed, Token &tok)
{
  if (allowed == allowCloseParen) {
    in_->ungetToken();
    tok = tokenCloseParen;
    message(InterpreterMessages::missingCloseParen);
    return 1;
  }
  if (in_->currentTokenLength() == 0)
    message(InterpreterMessages::unexpectedEof);
  else
    message(InterpreterMessages::unexpectedToken,
            StringMessageArg(StringC(in_->currentTokenStart(),
	                             in_->currentTokenLength())));
  return 0;
}
