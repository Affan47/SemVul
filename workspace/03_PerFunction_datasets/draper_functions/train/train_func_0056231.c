cancelAction()
{
  kDebug() << "KGameWindow::cancelAction";
  QByteArray buffer;
  QDataStream stream(&buffer, QIODevice::WriteOnly);
  stream << "";
  m_automaton->sendMessage(buffer,FirstCountry);
  QByteArray buffer2;
  QDataStream stream2(&buffer2, QIODevice::WriteOnly);
  stream2 << "";
  m_automaton->sendMessage(buffer2,SecondCountry);

  clearHighlighting();

  KMessageParts messageParts;
  QPixmap pm = currentPlayer()->getFlag()->image(0);
  messageParts
    << pm
    << I18N_NOOP("%1, it is up to you.") << currentPlayer()->name();
  broadcastChangeItem(messageParts, ID_STATUS_MSG2);
}
