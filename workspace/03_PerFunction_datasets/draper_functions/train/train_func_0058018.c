setBlocking(bool b)
{
    if (!b) {
        kWarning(7029) << "Caller requested non-blocking mode, but that doesn't work";
        return;
    }
    d->isBlocking = b;
}
