removePendingItems(int priority)
{
  lock();
  myQueue.remove_if<ItemComparator_PriorityLessThan>(ItemComparator_PriorityLessThan(priority));
  unlock();
}
