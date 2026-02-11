New() const {
  void* new_base = reinterpret_cast<uint8*>(operator new(type_info_->size));
  memset(new_base, 0, type_info_->size);
  return new(new_base) DynamicMessage(type_info_);
}
