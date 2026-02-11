SweepSpace(PagedSpace* space, DeallocateFunction dealloc) {
  PageIterator it(space, PageIterator::PAGES_IN_USE);
  while (it.has_next()) {
    Page* p = it.next();

    bool is_previous_alive = true;
    Address free_start = NULL;
    HeapObject* object;

    for (Address current = p->ObjectAreaStart();
         current < p->AllocationTop();
         current += object->Size()) {
      object = HeapObject::FromAddress(current);
      if (object->IsMarked()) {
        object->ClearMark();
        MarkCompactCollector::tracer()->decrement_marked_count();
        if (!is_previous_alive) {
          dealloc(free_start, static_cast<int>(current - free_start));
          is_previous_alive = true;
        }
      } else {
        MarkCompactCollector::ReportDeleteIfNeeded(object);
        if (is_previous_alive) {
          free_start = current;
          is_previous_alive = false;
        }
      }


    }


    if (!is_previous_alive) {
      int free_size = static_cast<int>(p->AllocationTop() - free_start);
      if (free_size > 0) {
        dealloc(free_start, free_size);
      }
    }
  }
}
