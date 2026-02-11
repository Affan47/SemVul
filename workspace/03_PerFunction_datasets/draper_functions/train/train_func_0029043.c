grow(bump_allocator* vm_nursery, cell requested_bytes) {
  FACTOR_ASSERT(vm_nursery->occupied_space() == 0);
  cell new_tenured_size = (tenured_size * 2) + requested_bytes;
  return new data_heap(vm_nursery, young_size, aging_size, new_tenured_size);
}
