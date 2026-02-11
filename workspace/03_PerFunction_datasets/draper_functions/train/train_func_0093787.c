EmptyMarkingStack() {
  while (!marking_stack_.is_empty()) {
    while (!marking_stack_.is_empty()) {
      HeapObject* object = marking_stack_.Pop();
      ASSERT(object->IsHeapObject());
      ASSERT(heap()->Contains(object));
      ASSERT(object->IsMarked());
      ASSERT(!object->IsOverflowed());


      MapWord map_word = object->map_word();
      map_word.ClearMark();
      Map* map = map_word.ToMap();
      MarkObject(map);

      StaticMarkingVisitor::IterateBody(map, object);
    }


    ProcessWeakMaps();
  }
}
