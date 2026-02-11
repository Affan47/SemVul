removeChildRange(SmartRange* child)
{
  DEBUG_CHILD_OVERLAP

  int index = findIndex(m_childRanges, child, child);
  if (index != -1) {
    m_childRanges.removeAt(index);


    for(int current = index-1; current >= 0; --current) {
      SmartRange& range(*m_childRanges[current]);
      Q_ASSERT(range.end() <= child->end());
      if(range.end() <= child->start()) {
        break;
      }else{
        if(range.m_overlapCount) {
          --range.m_overlapCount;
        } else {

#ifdef SHOULD_DEBUG_OVERLAP
          Q_ASSERT(0);
#endif
        }
      }
    }

    DEBUG_CHILD_OVERLAP

    child->m_overlapCount = 0;

    foreach (SmartRangeNotifier* n, m_notifiers)
      emit n->childRangeInserted(this, child);

    foreach (SmartRangeWatcher* w, m_watchers)
      w->childRangeInserted(this, child);
  }

  DEBUG_CHILD_OVERLAP
}
