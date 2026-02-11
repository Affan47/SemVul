BuildStoreKeyedPixelArrayElement(
    HValue* object,
    HValue* key,
    HValue* val,
    Expression* expr) {
  ASSERT(expr->IsMonomorphic());
  AddInstruction(new HCheckNonSmi(object));
  Handle<Map> map = expr->GetMonomorphicReceiverType();
  ASSERT(!map->has_fast_elements());
  ASSERT(map->has_pixel_array_elements());
  AddInstruction(new HCheckMap(object, map));
  HLoadElements* elements = new HLoadElements(object);
  AddInstruction(elements);
  HInstruction* length = AddInstruction(new HPixelArrayLength(elements));
  AddInstruction(new HBoundsCheck(key, length));
  HLoadPixelArrayExternalPointer* external_elements =
      new HLoadPixelArrayExternalPointer(elements);
  AddInstruction(external_elements);
  return new HStorePixelArrayElement(external_elements, key, val);
}
