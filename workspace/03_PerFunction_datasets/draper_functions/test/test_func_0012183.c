currentPlayer()
{
  if (m_game && !m_currentPlayer.isEmpty())
  {
    return playerNamed(m_currentPlayer);
  }
  else return 0;
}
