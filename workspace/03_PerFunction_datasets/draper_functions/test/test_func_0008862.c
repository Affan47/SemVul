reset()
{
    for(int c = White; c <= Black; ++c)
    {
        for(int r = 0; r < 4; ++r)
        {
            m_result[r] = 0;
        }
    }
    m_playersWhite.clear();
    m_playersBlack.clear();
    m_gamesWhite.clear();
    m_gamesBlack.clear();
    m_count = 0;
    m_rating[0] = 99999;
    m_rating[1] = 0;
}
