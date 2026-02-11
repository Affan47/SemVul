createBinary(StringRef Path) {
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
      MemoryBuffer::getFileOrSTDIN(Path);
  if (std::error_code EC = FileOrErr.getError())
    return EC;
  std::unique_ptr<MemoryBuffer> &Buffer = FileOrErr.get();

  ErrorOr<std::unique_ptr<Binary>> BinOrErr =
      createBinary(Buffer->getMemBufferRef());
  if (std::error_code EC = BinOrErr.getError())
    return EC;
  std::unique_ptr<Binary> &Bin = BinOrErr.get();

  return OwningBinary<Binary>(std::move(Bin), std::move(Buffer));
}
