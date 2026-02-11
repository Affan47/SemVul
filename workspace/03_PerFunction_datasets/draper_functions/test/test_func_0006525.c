Append(String* str) {
  AssertNoAllocation no_heap_allocation;
  int length = str->length();
  for (int i = 0; i < length; i++) {
    Append(static_cast<char>(str->Get(i)));
  }
}
