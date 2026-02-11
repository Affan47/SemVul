GC(const v8::Arguments& args) {
  bool compact = false;

  if (args.Length() >= 1 && args[0]->IsBoolean()) {
    compact = args[0]->BooleanValue();
  }
  HEAP->CollectAllGarbage(compact);
  return v8::Undefined();
}
