update()
{
  if (!_dirty) return;

  clear();
  TracePartInstrJump* item;
  for (item = _first; item; item = item->next()) {
    if (!item->part() || !item->part()->isActive()) continue;

    addCost(item);
  }
  _dirty = false;

#if TRACE_DEBUG
  qDebug("updated %s", qPrintable( fullName() ));
#endif

#if TRACE_DEBUG
  qDebug("   > %s", qPrintable(costString(0)));
#endif
}
