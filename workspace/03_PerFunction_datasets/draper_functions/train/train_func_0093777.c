createMatchTree (const std::vector<Player> &players)
{
    assert ( (2 == players.size () || 4 == players.size ()) &&
             "Currently only tournaments of 2 or 4 players are supported." );


    Player sentinelPlayer;
    sentinelPlayer.characterIndex = k_InvalidCharacterIndex;


    m_Matches.parent = 0;
    m_Matches.opponents.first = sentinelPlayer;
    m_Matches.opponents.second = sentinelPlayer;
    m_Matches.children.second = 0;

    Match *semifinal = new Match;
    semifinal->parent = &m_Matches;
    if ( 2 == players.size () )
    {
        m_HorizontalOffset.push_back (0);
        m_HorizontalOffset.push_back (192);
        m_VerticalPosition.push_back (288);
        m_VerticalPosition.push_back (544);

        semifinal->opponents.first = players[0];
        semifinal->opponents.first.score = 0;
        semifinal->opponents.second = players[1];
        semifinal->opponents.second.score = 0;
        semifinal->children.first = 0;
        semifinal->children.second = 0;
        m_Matches.children.first = semifinal;

        m_CurrentMatch = semifinal;
    }
    else
    {
        m_HorizontalOffset.push_back (0);
        m_HorizontalOffset.push_back (321);
        m_HorizontalOffset.push_back (192);
        m_VerticalPosition.push_back (160);
        m_VerticalPosition.push_back (416);
        m_VerticalPosition.push_back (672);

        semifinal->opponents.first = sentinelPlayer;
        semifinal->opponents.second = sentinelPlayer;
        m_Matches.children.first = semifinal;

        Match *leftMatch = new Match;
        leftMatch->children.first = 0;
        leftMatch->children.second = 0;
        leftMatch->parent = semifinal;
        leftMatch->opponents.first = players[0];
        leftMatch->opponents.first.score = 0;
        leftMatch->opponents.second = players[1];
        leftMatch->opponents.second.score = 0;

        Match *rightMatch = new Match;
        rightMatch->children.first = 0;
        rightMatch->children.second = 0;
        rightMatch->parent = semifinal;
        rightMatch->opponents.first = players[2];
        rightMatch->opponents.first.score = 0;
        rightMatch->opponents.second = players[3];
        rightMatch->opponents.second.score = 0;

        semifinal->children.first = leftMatch;
        semifinal->children.second = rightMatch;

        m_CurrentMatch = leftMatch;
    }
}
