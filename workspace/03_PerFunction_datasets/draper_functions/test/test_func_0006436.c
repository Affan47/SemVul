handleTimer(YTimer *timer) {
    if (timer == fAutoScrollTimer && fWindow) {
        fAutoScrollTimer->setInterval(autoScrollDelay);
        return fWindow->handleAutoScroll(*fMotion);
    }
    return false;
}
