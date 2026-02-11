Add(Vector<const char> name, Handle<SharedFunctionInfo> shared) {
    HandleScope scope;
    int length = cache_->length();
    Handle<FixedArray> new_array =
        Factory::NewFixedArray(length + 2, TENURED);
    cache_->CopyTo(0, *new_array, 0, cache_->length());
    cache_ = *new_array;
    Handle<String> str = Factory::NewStringFromAscii(name, TENURED);
    cache_->set(length, *str);
    cache_->set(length + 1, *shared);
    Script::cast(shared->script())->set_type(Smi::FromInt(type_));
  }
