update()
{

    for (int i = 0; i < m_bombs.size(); ++i)
    {
        m_bombs[i]->updateMove();
    }


    for(int i = 0; i < m_players.size(); i++)
    {
        m_players[i]->updateMove();
        m_players[i]->emitGameUpdated();
    }
}
