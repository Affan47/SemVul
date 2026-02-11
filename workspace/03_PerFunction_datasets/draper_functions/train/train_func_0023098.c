endOfMatch (IPlayer::PlayerSide winner,
                          uint32_t leftPlayerScore, uint32_t rightPlayerScore)
{
    m_Winner = winner;
    if ( k_PlayerSide == winner )
    {
        m_SoundWin->play ();
        incrementOpponentLevel ();

        m_CurrentScore = k_PlayerSide == IPlayer::LeftSide ? leftPlayerScore :
                                                             rightPlayerScore;
    }
    else
    {
        m_SoundLose->play ();
        askTryAgain ();
    }
}
