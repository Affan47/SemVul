CopyFixedArrayWithMap(FixedArray* src, Map* map) {
  int len = src->length();
  Object* obj;
  { MaybeObject* maybe_obj = AllocateRawFixedArray(len);
    if (!maybe_obj->ToObject(&obj)) return maybe_obj;
  }
  if (InNewSpace(obj)) {
    HeapObject* dst = HeapObject::cast(obj);
    dst->set_map(map);
    CopyBlock(dst->address() + kPointerSize,
              src->address() + kPointerSize,
              FixedArray::SizeFor(len) - kPointerSize);
    return obj;
  }
  HeapObject::cast(obj)->set_map(map);
  FixedArray* result = FixedArray::cast(obj);
  result->set_length(len);


  AssertNoAllocation no_gc;
  WriteBarrierMode mode = result->GetWriteBarrierMode(no_gc);
  for (int i = 0; i < len; i++) result->set(i, src->get(i), mode);
  return result;
}
