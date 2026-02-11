handleTimer(YTimer *t) {
    if (t == fRaiseTimer) {
        getFrame()->wmRaise();
    }
    return false;
}
