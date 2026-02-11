activate (void)
{
    getLeftPlayer ()->loadOptions ();
    getRightPlayer ()->loadOptions ();
    if ( Music::isPaused () )
    {
        Music::resume ();
    }
    else
    {
        m_BackgroundMusic->play ();
    }
}
