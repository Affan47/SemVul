handleCrossing(const XCrossingEvent &crossing) {
    if (fToolTip) {
        if (crossing.type == EnterNotify && crossing.mode == NotifyNormal) {
            if (fToolTipTimer == 0)
                fToolTipTimer = new YTimer(ToolTipDelay);
            if (fToolTipTimer) {
                fToolTipTimer->setTimerListener(fToolTip);
                fToolTipTimer->startTimer();
                updateToolTip();
                if (fToolTip)
                    fToolTip->locate(this, crossing);
            }
        } else if (crossing.type == LeaveNotify) {
            fToolTip->hide();
            if (fToolTipTimer && fToolTipTimer->getTimerListener() == fToolTip) {
                fToolTipTimer->stopTimer();
                fToolTipTimer->setTimerListener(0);
            }
        }
    }
#endif
}
