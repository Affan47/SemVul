update()
{
  if (!_dirty) return;

#if TRACE_DEBUG
  qDebug("update %s (count %d)",
         qPrintable( fullName() ), _deps.count());
#endif

  clear();
  foreach(TraceInclusiveCost* item, _deps) {
    if (onlyActiveParts())
      if (!item->part() || !item->part()->isActive()) continue;

    addCost(item);
    addInclusive(item->inclusive());
  }

  _dirty = false;

#if TRACE_DEBUG
  qDebug("   > %s", qPrintable(costString(0)));
#endif
}
