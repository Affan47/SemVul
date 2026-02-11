popQueueItem_NoLock()
{
  ArSoundsQueue::Item item = *(myQueue.begin());
  myQueue.pop_front();
  return item;
}
