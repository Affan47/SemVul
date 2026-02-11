removePendingItems(const char* item, ItemType type)
{
  lock();
  myQueue.remove_if<ItemComparator_TypeAndData>(ItemComparator_TypeAndData(item, type));
  unlock();
}
