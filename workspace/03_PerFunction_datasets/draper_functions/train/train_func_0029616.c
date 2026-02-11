HasSourceCode(SharedFunctionInfo* info) {
    Object* undefined = Heap::raw_unchecked_undefined_value();
    return (info->script() != undefined) &&
        (reinterpret_cast<Script*>(info->script())->source() != undefined);
  }
