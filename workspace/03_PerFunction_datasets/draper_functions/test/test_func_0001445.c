startScore(Char c)
{
  CharArgCall::FuncPtr func = &FOTBuilder::startScore;
  *tail_ = new CharArgCall(func, c);
  tail_ = &(*tail_)->next;
}
