anyRunningDisplays(void)
{
    struct display *d;

    for (d = displays; d; d = d->next)
        switch (d->status) {
        case notRunning:
        case textMode:
        case reserve:
            break;
        default:
            return True;
        }
    return False;
}
