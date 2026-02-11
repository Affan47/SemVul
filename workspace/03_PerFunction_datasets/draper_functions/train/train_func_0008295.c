Setup(Address start, int size) {


  int initial_semispace_capacity = heap()->InitialSemiSpaceSize();
  int maximum_semispace_capacity = heap()->MaxSemiSpaceSize();

  ASSERT(initial_semispace_capacity <= maximum_semispace_capacity);
  ASSERT(IsPowerOf2(maximum_semispace_capacity));


  allocated_histogram_ = NewArray<HistogramInfo>(LAST_TYPE + 1);
  promoted_histogram_ = NewArray<HistogramInfo>(LAST_TYPE + 1);

#define SET_NAME(name) allocated_histogram_[name].set_name(#name); \
                       promoted_histogram_[name].set_name(#name);
  INSTANCE_TYPE_LIST(SET_NAME)
#undef SET_NAME

  ASSERT(size == 2 * heap()->ReservedSemiSpaceSize());
  ASSERT(IsAddressAligned(start, size, 0));

  if (!to_space_.Setup(start,
                       initial_semispace_capacity,
                       maximum_semispace_capacity)) {
    return false;
  }
  if (!from_space_.Setup(start + maximum_semispace_capacity,
                         initial_semispace_capacity,
                         maximum_semispace_capacity)) {
    return false;
  }

  start_ = start;
  address_mask_ = ~(size - 1);
  object_mask_ = address_mask_ | kHeapObjectTagMask;
  object_expected_ = reinterpret_cast<uintptr_t>(start) | kHeapObjectTag;

  allocation_info_.top = to_space_.low();
  allocation_info_.limit = to_space_.high();
  mc_forwarding_info_.top = NULL;
  mc_forwarding_info_.limit = NULL;

  ASSERT_SEMISPACE_ALLOCATION_INFO(allocation_info_, to_space_);
  return true;
}
