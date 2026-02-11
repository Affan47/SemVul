create(MemoryBufferRef Object, LLVMContext &Context,
                                const Module *ExportingModule, bool IsLazy) {
  std::unique_ptr<FunctionInfoIndex> Index;

  ErrorOr<MemoryBufferRef> BCOrErr = findBitcodeInMemBuffer(Object);
  if (!BCOrErr)
    return BCOrErr.getError();

  ErrorOr<std::unique_ptr<FunctionInfoIndex>> IOrErr = getFunctionInfoIndex(
      BCOrErr.get(), Context, nullptr, ExportingModule, IsLazy);

  if (std::error_code EC = IOrErr.getError())
    return EC;

  Index = std::move(IOrErr.get());

  return llvm::make_unique<FunctionIndexObjectFile>(Object, std::move(Index));
}
