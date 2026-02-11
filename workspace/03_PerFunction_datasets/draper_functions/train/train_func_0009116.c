CallIsMonomorphic(Call* expr) {
  Handle<Object> value = GetElement(map_, expr->position());
  return value->IsMap() || value->IsSmi();
}
