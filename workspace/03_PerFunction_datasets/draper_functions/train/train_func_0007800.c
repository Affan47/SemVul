UpdateMapPointersInLargeObjectSpace() {
    LargeObjectIterator it(Heap::lo_space());
    for (HeapObject* obj = it.next(); obj != NULL; obj = it.next())
      UpdateMapPointersInObject(obj);
  }
