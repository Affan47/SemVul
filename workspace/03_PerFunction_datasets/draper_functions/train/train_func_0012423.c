handleTimer(YTimer *t) {
    if (t != fUpdateTimer)
        return false;
    if (toolTipVisible())
        updateToolTip();
    updateStatus();
    return true;
}
