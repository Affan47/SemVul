AllocateStruct(InstanceType type) {
  Map* map;
  switch (type) {
#define MAKE_CASE(NAME, Name, name) case NAME##_TYPE: map = name##_map(); break;
STRUCT_LIST(MAKE_CASE)
#undef MAKE_CASE
    default:
      UNREACHABLE();
      return Failure::InternalError();
  }
  int size = map->instance_size();
  AllocationSpace space =
      (size > MaxObjectSizeInPagedSpace()) ? LO_SPACE : OLD_POINTER_SPACE;
  Object* result;
  { MaybeObject* maybe_result = Heap::Allocate(map, space);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }
  Struct::cast(result)->InitializeBody(size);
  return result;
}
