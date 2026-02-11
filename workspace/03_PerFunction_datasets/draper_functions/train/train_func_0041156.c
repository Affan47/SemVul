findScorePosition (uint32_t score)
{
    std::list<HighScore>::iterator currentScore;
    for (currentScore = m_HighScore.begin();
         currentScore != m_HighScore.end();
         ++currentScore)
    {
        if ( score > currentScore->first )
        {
            break;
        }
    }

    return currentScore;
}
