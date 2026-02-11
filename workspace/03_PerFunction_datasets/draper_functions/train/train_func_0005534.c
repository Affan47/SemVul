MarkObjectByPointer(Object** p) {
    if (!(*p)->IsHeapObject()) return;


    HeapObject* object = ShortCircuitConsString(p);
    if (object->IsMarked()) return;

    Map* map = object->map();

    collector_->SetMark(object);


    collector_->MarkObject(map);
    StaticMarkingVisitor::IterateBody(map, object);


    collector_->EmptyMarkingStack();
  }
