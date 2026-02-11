matchSessionComplete()
{
    if (!d->prepped) {
        return;
    }

    d->teardownRequested = true;
    d->checkTearDown();
}
