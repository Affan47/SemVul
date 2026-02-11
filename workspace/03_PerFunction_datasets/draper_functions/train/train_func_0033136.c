handleFocus(const XFocusChangeEvent &focus) {
    if (focus.type == FocusIn
        && focus.detail != NotifyPointer && focus.detail != NotifyPointerRoot)
    {
        fHasFocus = true;
        selectAll();
        if (cursorBlinkTimer == 0)
            cursorBlinkTimer = new YTimer(300);
        if (cursorBlinkTimer) {
            cursorBlinkTimer->setTimerListener(this);
            cursorBlinkTimer->startTimer();
        }
    } else if (focus.type == FocusOut) {
        fHasFocus = false;
        repaint();
        if (cursorBlinkTimer) {
            if (cursorBlinkTimer->getTimerListener() == this) {
                cursorBlinkTimer->stopTimer();
                cursorBlinkTimer->setTimerListener(0);
            }
        }
    }
}
