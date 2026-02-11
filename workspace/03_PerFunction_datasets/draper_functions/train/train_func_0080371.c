nextPlayerNormal()
{
  kDebug() << " (current is" << currentPlayer()->name()<<")";
  setCurrentPlayerToNext();
  distributeArmies();

  QByteArray buffer;
  m_automaton->sendMessage(buffer,ShowArmiesToPlace);

  clear();
  QByteArray buffer2;
  m_automaton->sendMessage(buffer2,StartLocalCurrentAI);
  getRightDialog()->close();

  QByteArray buffer3;
  QDataStream stream3(&buffer3, QIODevice::WriteOnly);
  stream3 << currentPlayer()-> name();
  stream3 << (quint32)nbNewArmies(currentPlayer());
  kDebug() << "sending DisplayRecycleDetails "
      << currentPlayer()->name() << nbNewArmies(currentPlayer())
      << " at " << __FILE__ << ", line " << __LINE__;
  m_automaton->sendMessage(buffer3,DisplayRecycleDetails);
  return true;
}
