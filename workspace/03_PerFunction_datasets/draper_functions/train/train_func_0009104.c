pause()
{
    if (is_paused) {
        gameTimer->resume();
    } else {
        gameTimer->pause();
    }

    is_paused = !is_paused;
    demoModeChanged(false);
    bw->pause();
}
