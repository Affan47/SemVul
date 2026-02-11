CallRuntimeSaveDoubles(Runtime::FunctionId id) {
  Runtime::Function* function = Runtime::FunctionForId(id);
  Set(rax, function->nargs);
  movq(rbx, ExternalReference(function));
  CEntryStub ces(1);
  ces.SaveDoubles();
  CallStub(&ces);
}
