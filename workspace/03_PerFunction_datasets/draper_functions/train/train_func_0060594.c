HasRealElementProperty(uint32_t index) {

  if (IsAccessCheckNeeded()) {
    Heap* heap = GetHeap();
    if (!heap->isolate()->MayIndexedAccess(this, index, v8::ACCESS_HAS)) {
      heap->isolate()->ReportFailedAccessCheck(this, v8::ACCESS_HAS);
      return false;
    }
  }


  if (this->IsStringObjectWithCharacterAt(index)) return true;

  switch (GetElementsKind()) {
    case FAST_ELEMENTS: {
      uint32_t length = IsJSArray() ?
          static_cast<uint32_t>(
              Smi::cast(JSArray::cast(this)->length())->value()) :
          static_cast<uint32_t>(FixedArray::cast(elements())->length());
      return (index < length) &&
          !FixedArray::cast(elements())->get(index)->IsTheHole();
    }
    case FAST_DOUBLE_ELEMENTS: {
      uint32_t length = IsJSArray() ?
          static_cast<uint32_t>(
              Smi::cast(JSArray::cast(this)->length())->value()) :
          static_cast<uint32_t>(FixedDoubleArray::cast(elements())->length());
      return (index < length) &&
          !FixedDoubleArray::cast(elements())->is_the_hole(index);
      break;
    }
    case EXTERNAL_PIXEL_ELEMENTS: {
      ExternalPixelArray* pixels = ExternalPixelArray::cast(elements());
      return index < static_cast<uint32_t>(pixels->length());
    }
    case EXTERNAL_BYTE_ELEMENTS:
    case EXTERNAL_UNSIGNED_BYTE_ELEMENTS:
    case EXTERNAL_SHORT_ELEMENTS:
    case EXTERNAL_UNSIGNED_SHORT_ELEMENTS:
    case EXTERNAL_INT_ELEMENTS:
    case EXTERNAL_UNSIGNED_INT_ELEMENTS:
    case EXTERNAL_FLOAT_ELEMENTS:
    case EXTERNAL_DOUBLE_ELEMENTS: {
      ExternalArray* array = ExternalArray::cast(elements());
      return index < static_cast<uint32_t>(array->length());
    }
    case DICTIONARY_ELEMENTS: {
      return element_dictionary()->FindEntry(index)
          != NumberDictionary::kNotFound;
    }
    case NON_STRICT_ARGUMENTS_ELEMENTS:
      UNIMPLEMENTED();
      break;
  }

  UNREACHABLE();
  return GetHeap()->null_value();
}
