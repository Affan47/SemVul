FreeUnmarkedObjects() {
  LargeObjectChunk* previous = NULL;
  LargeObjectChunk* current = first_chunk_;
  while (current != NULL) {
    HeapObject* object = current->GetObject();
    if (object->IsMarked()) {
      object->ClearMark();
      heap()->mark_compact_collector()->tracer()->decrement_marked_count();
      previous = current;
      current = current->next();
    } else {

      LargeObjectChunk* current_chunk = current;
      current = current->next();
      if (previous == NULL) {
        first_chunk_ = current;
      } else {
        previous->set_next(current);
      }


      heap()->mark_compact_collector()->ReportDeleteIfNeeded(
          object, heap()->isolate());
      LiveObjectList::ProcessNonLive(object);

      size_ -= static_cast<int>(current_chunk->size());
      objects_size_ -= object->Size();
      page_count_--;
      current_chunk->Free(current_chunk->GetPage()->PageExecutability());
    }
  }
}
