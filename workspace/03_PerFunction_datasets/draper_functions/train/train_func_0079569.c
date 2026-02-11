CheckProperty(
    ObjectLiteral::Property* property,
    Scanner::Location loc,
    bool* ok) {

  ASSERT(property != NULL);

  Literal *lit = property->key();
  Handle<Object> handle = lit->handle();

  uint32_t hash;
  HashMap* map;
  void* key;

  if (handle->IsSymbol()) {
    Handle<String> name(String::cast(*handle));
    if (name->AsArrayIndex(&hash)) {
      Handle<Object> key_handle = Factory::NewNumberFromUint(hash);
      key = key_handle.location();
      map = &elems;
    } else {
      key = handle.location();
      hash = name->Hash();
      map = &props;
    }
  } else if (handle->ToArrayIndex(&hash)) {
    key = handle.location();
    map = &elems;
  } else {
    ASSERT(handle->IsNumber());
    double num = handle->Number();
    char arr[100];
    Vector<char> buffer(arr, ARRAY_SIZE(arr));
    const char* str = DoubleToCString(num, buffer);
    Handle<String> name = Factory::NewStringFromAscii(CStrVector(str));
    key = name.location();
    hash = name->Hash();
    map = &props;
  }


  HashMap::Entry* entry = map->Lookup(key, hash, true);
  intptr_t prev = reinterpret_cast<intptr_t> (entry->value);
  intptr_t curr = GetPropertyKind(property);


  if (strict_ && (curr & prev & kData) != 0) {
    parser_->ReportMessageAt(loc, "strict_duplicate_property",
                             Vector<const char*>::empty());
    *ok = false;
    return;
  }

  if (((curr & kData) && (prev & kAccessor)) ||
      ((prev & kData) && (curr & kAccessor))) {
    parser_->ReportMessageAt(loc, "accessor_data_property",
                             Vector<const char*>::empty());
    *ok = false;
    return;
  }

  if ((curr & prev & kAccessor) != 0) {
    parser_->ReportMessageAt(loc, "accessor_get_set",
                             Vector<const char*>::empty());
    *ok = false;
    return;
  }


  entry->value = reinterpret_cast<void*> (prev | curr);
  *ok = true;
}
