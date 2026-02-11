setCurrentPlayerToFirst()
{
  if (currentPlayer() && currentPlayer()->isAI()
                      && (static_cast<AIPlayer *>(currentPlayer())->isRunning()))
  {
        static_cast<AIPlayer *>(currentPlayer())->stop();
  }
  m_automaton->currentPlayer((Player*)(*m_automaton->playerList()->begin()));


  m_frame->setFocus();
  return 0;
}
