DequeueEvent(long usec)
{
    return ((usec < 0) ? semaphore.Wait() : semaphore.TimedWait(usec)) ?
        JackMidiAsyncQueue::DequeueEvent() : 0;
}
