handleTimer(YTimer *t) {
    if (t == fRaiseTimer) {
        getFrame()->wmRaise();
    }
    if (t == fFlashTimer) {
        if (!fFlashing) {
            fFlashOn = 0;
            fFlashStart = 0;
            return false;
        }
        fFlashOn = !fFlashOn;
        if (focusRequestFlashTime != 0) {
            if (time(NULL) - fFlashStart > focusRequestFlashTime)
                fFlashing = false;
        }
        repaint();
        return fFlashing;
    }
    return false;
}
