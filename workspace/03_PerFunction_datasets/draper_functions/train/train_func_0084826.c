SessionIsOpen()
  {
    return (!GetSession().isNull() && !GetSession()->GetCurrentRound().isNull());
  }
