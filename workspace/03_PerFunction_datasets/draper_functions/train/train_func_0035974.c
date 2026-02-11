AsObject() {
    if (hash_field_ == 0) Hash();
    return Isolate::Current()->heap()->AllocateSymbol(
        string_, chars_, hash_field_);
  }
