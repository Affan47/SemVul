customEvent(QEvent* e)
{
    if (e->type() == CompletionMatchEvent::uniqueType()) {

        CompletionMatchEvent* matchEvent = static_cast<CompletionMatchEvent*>(e);

        matchEvent->completionThread()->wait();

        if (!d->isListedUrl(CTUser)) {
            stop();
            clear();
            d->addMatches(matchEvent->completionThread()->matches());
        } else {
            d->setListedUrl(CTUser);
        }

        if (d->userListThread == matchEvent->completionThread())
            d->userListThread = 0;

        if (d->dirListThread == matchEvent->completionThread())
            d->dirListThread = 0;

        delete matchEvent->completionThread();
    }
}
