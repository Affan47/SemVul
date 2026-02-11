inLoop(const Location &loc)
{
  const InputSourceOrigin *origin = paramLoc_.origin()->asInputSourceOrigin();
  if (!origin)
    return 0;
  const ExternalInfo *info = origin->externalInfo();
  if (!info)
    return 0;
  StorageObjectLocation soLoc;
  if (!ExtendEntityManager::externalize(info,
					origin->startOffset(paramLoc_.index()),
					soLoc))
    return 0;
  for (;;) {
    const Location &parent = origin->parent();
    if (parent.origin().isNull())
      break;
    origin = parent.origin()->asInputSourceOrigin();
    if (!origin)
      break;
    const ExternalInfo *info1 = origin->externalInfo();
    if (info1) {
      StorageObjectLocation soLoc1;
      if (ExtendEntityManager::externalize(info1,
					   origin->startOffset(parent.index()),
					   soLoc1)) {
	if (soLoc.storageObjectSpec->storageManager
	    == soLoc1.storageObjectSpec->storageManager
	    && soLoc.actualStorageId == soLoc1.actualStorageId) {
	  setNextLocation(loc.origin()->parent());
	  message(CatalogMessages::inLoop);
	  return 1;
	}
      }
    }
  }
  return 0;
}
