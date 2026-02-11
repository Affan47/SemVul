setSortOrder(SortOrder newOrder)
{
  if (_sortOrder == newOrder) return;

  SMSStoreMap savedSMSStore = _sortedSMSStore;
  _sortedSMSStore = SMSStoreMap();
  _sortOrder = newOrder;

  switch (newOrder)
  {
  case ByIndex:
  {
    for (SMSStoreMap::iterator i = savedSMSStore.begin();
         i != savedSMSStore.end(); ++i)
      _sortedSMSStore.insert(
        SMSStoreMap::value_type(SMSMapKey(*this, (i->second->index())),
                                i->second));
    break;
  }
  case ByDate:
  {
    for (SMSStoreMap::iterator i = savedSMSStore.begin();
         i != savedSMSStore.end(); ++i)
      _sortedSMSStore.insert(
        SMSStoreMap::value_type(
          SMSMapKey(*this, (i->second->message()->serviceCentreTimestamp())),
          i->second));
    break;
  }
  case ByAddress:
  {
    for (SMSStoreMap::iterator i = savedSMSStore.begin();
         i != savedSMSStore.end(); ++i)
      _sortedSMSStore.insert(
        SMSStoreMap::value_type(
          SMSMapKey(*this, (i->second->message()->address())),
          i->second));
    break;
  }
  case ByType:
  {
    for (SMSStoreMap::iterator i = savedSMSStore.begin();
         i != savedSMSStore.end(); ++i)
      _sortedSMSStore.insert(
        SMSStoreMap::value_type(
          SMSMapKey(*this, (i->second->message()->messageType())),
          i->second));
    break;
  }
  default:
    assert(0);
    break;
  }
}
