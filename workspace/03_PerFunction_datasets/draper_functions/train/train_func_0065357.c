LeftTrimFixedArray(FixedArray* elms, int to_trim) {
  ASSERT(elms->map() != Heap::fixed_cow_array_map());


  ASSERT(!Heap::lo_space()->Contains(elms));

  STATIC_ASSERT(FixedArray::kMapOffset == 0);
  STATIC_ASSERT(FixedArray::kLengthOffset == kPointerSize);
  STATIC_ASSERT(FixedArray::kHeaderSize == 2 * kPointerSize);

  Object** former_start = HeapObject::RawField(elms, 0);

  const int len = elms->length();

  if (to_trim > FixedArray::kHeaderSize / kPointerSize &&
      !Heap::new_space()->Contains(elms)) {


    Object** zap = reinterpret_cast<Object**>(elms->address());
    zap++;
    for (int i = 1; i < to_trim; i++) {
      *zap++ = Smi::FromInt(0);
    }
  }


  Heap::CreateFillerObjectAt(elms->address(), to_trim * kPointerSize);

  former_start[to_trim] = Heap::fixed_array_map();
  former_start[to_trim + 1] = Smi::FromInt(len - to_trim);

  return FixedArray::cast(HeapObject::FromAddress(
      elms->address() + to_trim * kPointerSize));
}
