removeStateStreams(Object *obj1) {
  if (obj1->isRef()) {
    removeStream(obj1->getRef());
  } else if (obj1->isDict()) {
    const int size = obj1->dictGetLength();
    for (int i = 0; i < size; ++i) {
      Object obj2;
      obj1->dictGetValNF(i, &obj2);
      if (obj2.isRef()) {
        removeStream(obj2.getRef());
      }
      obj2.free();
    }
  }
}
