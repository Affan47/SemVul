Create (ClassId id) {
  void* ptr = create(id);
  return ptr ? ptr : OverlayCreator::Create(id);
}
