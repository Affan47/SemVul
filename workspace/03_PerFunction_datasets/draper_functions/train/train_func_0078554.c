CopyEnumKeysTo(FixedArray* storage,
                                      FixedArray* sort_array) {
  ASSERT(storage->length() >= NumberOfEnumElements());
  int capacity = Capacity();
  int index = 0;
  for (int i = 0; i < capacity; i++) {
     Object* k = KeyAt(i);
     if (IsKey(k)) {
       PropertyDetails details = DetailsAt(i);
       if (details.IsDeleted() || details.IsDontEnum()) continue;
       storage->set(index, k);
       sort_array->set(index, Smi::FromInt(details.index()));
       index++;
     }
  }
  storage->SortPairs(sort_array, sort_array->length());
  ASSERT(storage->length() >= index);
}
