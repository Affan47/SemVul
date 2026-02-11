slotRemoveDelayed()
{
  delayRemove = false;


  while (!removeList.isEmpty()) {
    Entry* entry = *removeList.begin();
    removeEntry(0, entry, 0);
  }
}
