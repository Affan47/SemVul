setStatus(long workspace) {
    this->workspace = workspace;
    repaintSync();

    if (timer->isRunning())
        timer->stopTimer();

    timer->startTimer();
}
