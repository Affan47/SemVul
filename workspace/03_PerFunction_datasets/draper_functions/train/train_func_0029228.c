onExit()
{
    RecursiveLock lock(_queueMutex);
    _exitLoop = true;
    lock.unlock();

    this->wake();
}
