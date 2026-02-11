AllocateFixedArray(int length, PretenureFlag pretenure) {
  ASSERT(length >= 0);
  ASSERT(empty_fixed_array()->IsFixedArray());
  if (length < 0 || length > FixedArray::kMaxLength) {
    return Failure::OutOfMemoryException();
  }
  if (length == 0) return empty_fixed_array();

  AllocationSpace space =
      (pretenure == TENURED) ? OLD_POINTER_SPACE : NEW_SPACE;
  int size = FixedArray::SizeFor(length);
  if (space == NEW_SPACE && size > kMaxObjectSizeInNewSpace) {

    space = LO_SPACE;
  } else if (space == OLD_POINTER_SPACE &&
             size > MaxObjectSizeInPagedSpace()) {

    space = LO_SPACE;
  }


  Object* result = Failure::OutOfMemoryException();
  if (space == NEW_SPACE) {


    result = new_space_.AllocateRaw(size);
    if (result->IsFailure() && always_allocate()) {
      if (size <= MaxObjectSizeInPagedSpace()) {
        result = old_pointer_space_->AllocateRaw(size);
      } else {
        result = lo_space_->AllocateRawFixedArray(size);
      }
    }
  } else if (space == OLD_POINTER_SPACE) {
    result = old_pointer_space_->AllocateRaw(size);
  } else {
    ASSERT(space == LO_SPACE);
    result = lo_space_->AllocateRawFixedArray(size);
  }
  if (result->IsFailure()) return result;


  reinterpret_cast<Array*>(result)->set_map(fixed_array_map());
  FixedArray* array = FixedArray::cast(result);
  array->set_length(length);
  ASSERT(!Heap::InNewSpace(undefined_value()));
  MemsetPointer(array->data_start(), undefined_value(), length);
  return array;
}
