actionRecycling()
{
  kDebug() << "KGameWindow::actionRecycling";
  setCurrentPlayerToFirst();
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::WriteOnly);
  m_automaton->sendMessage(buffer,StartLocalCurrentAI);
  QByteArray buffer2;
  QDataStream stream2(&buffer2, QIODevice::WriteOnly);
  stream2 << currentPlayer()->name();
  stream2 << (quint32)0;
  kDebug() << "sending DisplayRecycleDetails "
    << currentPlayer()->name() << 0
    << " at " << __FILE__ << ", line " << __LINE__;
  m_automaton->sendMessage(buffer2,DisplayRecycleDetails);

  QPixmap pm = currentPlayer()->getFlag()->image(0);
}
