setAutoHideTimeout(int msecs)
{
    d->autoHideTimeout = msecs;

    if (msecs > 0) {
        installEventFilter(this);
    } else {
        removeEventFilter(this);
    }
}
