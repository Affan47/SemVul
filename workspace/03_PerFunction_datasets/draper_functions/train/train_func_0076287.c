handleTimer(YTimer *t) {
    if (t == fAutoRaiseTimer) {
        if (canRaise())
            wmRaise();
    }
    if (t == fDelayFocusTimer)
        focus(false);
    return false;
}
