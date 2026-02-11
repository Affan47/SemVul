nextItem(int priority)
{
  lock();
  for(list<Item>::const_iterator i = myQueue.begin(); i != myQueue.end(); i++)
  {
    if((*i).priority >= priority) {
      string found = (*i).data;
      unlock();
      return found;
    }
  }
  unlock();
  return "";
}
