setReply(const Message &message)
{
    Q_ASSERT(message.id()==id);
    isFinished = true;
    reply = message;

    foreach (PendingCallWaiter *waiter, waiters) {
        waiter->eventLoop.quit();
    }
    waiters.clear();

    foreach (PendingCallWatcher *watcher, watchers) {
        emit watcher->finished(watcher);
    }
    watchers.clear();
}
