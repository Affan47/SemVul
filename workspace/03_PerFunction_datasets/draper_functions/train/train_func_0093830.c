removePendingItems(int priority, ItemType type)
{
  lock();
  myQueue.remove_if<ItemComparator_WithTypePriorityLessThan>(ItemComparator_WithTypePriorityLessThan(type, priority));
  unlock();
}
