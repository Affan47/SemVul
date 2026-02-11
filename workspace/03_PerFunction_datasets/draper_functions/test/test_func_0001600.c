pauseGame(bool paused)
{
    pause(paused);
    if(paused) {
        m_gameClock->pause();
    } else {
        m_gameClock->resume();
    }
}
