pass()
{
    if (m_game->playMove(m_game->currentPlayer())) {

        m_gameScene->showHint(false);
    }
}
