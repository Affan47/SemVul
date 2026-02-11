checkLevelChange (void)
{


    bool levelChanged = false;
    if ( getCurrentLevel () < k_NumLevels )
    {
        while ( getCurrentLevel () < k_NumLevels &&
                getPlayerGrid ()->getScore () > k_Levels[getCurrentLevel ()].minScore )
        {
            incrementCurrentLevel ();
            levelChanged = true;
        }

        if ( levelChanged )
        {
            m_LevelUpSound->play ();
            m_LevelUpPosition = Options::getInstance ().getScreenHeight () / 2;
            m_LevelUpTime = k_LevelUpTime;
        }
    }
}
