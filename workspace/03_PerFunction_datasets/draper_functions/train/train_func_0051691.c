IsUnscavengedHeapObject(Heap* heap, Object** p) {
  return heap->InNewSpace(*p) &&
      !HeapObject::cast(*p)->map_word().IsForwardingAddress();
}
