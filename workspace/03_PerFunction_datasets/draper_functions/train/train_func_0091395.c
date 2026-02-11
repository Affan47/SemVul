handleButton(const XButtonEvent &button) {
    if (handleScrollMouse(button) == true)
        return ;

    if (button.button != Button1)
        return ;

    if (fMinimum >= fMaximum)
        return ;

    if (button.type == ButtonPress) {
        fScrollTo = getOp(button.x, button.y);
        doScroll();
        if (fScrollTimer == 0)
            fScrollTimer = new YTimer(scrollBarStartDelay);
        if (fScrollTimer) {
            fScrollTimer->setInterval(scrollBarStartDelay);
            fScrollTimer->setTimerListener(this);
            fScrollTimer->startTimer();
        }
        repaint();
    } else if (button.type == ButtonRelease) {
        fScrollTo = goNone;
        if (fScrollTimer && fScrollTimer->getTimerListener() == this) {
            fScrollTimer->setTimerListener(0);
            fScrollTimer->stopTimer();
        }
        repaint();
    }
}
