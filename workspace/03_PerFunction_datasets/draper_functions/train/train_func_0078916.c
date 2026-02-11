pause (void)
{
    if ( 0 != m_ActiveState && m_ActiveState->shouldBePaused () )
    {
        setActiveState (new PauseState (), FadeNone);
    }
}
